#include "SavingLoadingIO.h"

namespace SavingLoadingIO
{
	int SaveProjectToFile(Model* in, std::string filename, bool overwrite)
	{
		std::ifstream test(filename);
		
		//if the file already exists (we were able to open it) and the overwrite flag is not set.... return error
		if (test.good() && overwrite == false)
		{
			return SaveAlreadyExists;
		}
		test.close();
		std::ofstream out(filename);

		//file is probably in use or could not be opened for another reason
		if (!out.good())
		{
			return SaveError;
		}

		out << "Hercules:\n";

		for (auto i : *in->ReturnClasses())
		{
			out << "  UMLObject:\n";
			out << "    Title:\n";
			out << "      - " << i.name() << "\n";
			for (auto j : *i.ReturnFields())
			{
				out << "    UMLField:\n";

				out << "      Name:\n";
				out << "        - " << j.name() << "\n";

				out << "      Type:\n";
				out << "        - " << j.type() << "\n";

				out << "      Visibility:\n";
				out << "        - " << j.visibility() << "\n";
			}

			for (auto j : *i.ReturnMethods())
			{
				out << "    UMLMethod:\n";

				out << "      Name:\n";
				out << "        - " << j.name() << "\n";

				out << "      Type:\n";
				out << "        - " << j.ReturnType() << "\n";

				out << "      Visibility:\n";
				out << "        - " << j.visibility() << "\n";

				out << "      Parameters:\n";

				for (auto k : *j.ReturnParameters())
				{
					out << "        UMLParameter:\n";

					out << "          Type:\n";
					out << "            - " << k.type()<< "\n";

					out << "          Name:\n";
					out << "            - " << k.name() << "\n";

				}
			}

			out << "    X:\n";
			out << "      - " << i.GetXPosition() << "\n";
			out << "    Y:\n";
			out << "      - " << i.GetYPosition() << "\n";
		}

		for (auto i : *in->ReturnRelationships())
		{
			out << "  UMLRelationship:\n";

			out << "    Type:\n";
			out << "      - " << ToString(i.type()) << "\n";

			out << "    Parent:\n";
			out << "      - " << i.parent().name() << "\n";

			out << "    Child:\n";
			out << "      - " << i.child().name() << "\n";
		}

		out.close();
		return SaveSuccess;
	}

	bool LoadProject(Model* out, std::string filename)
	{
		std::ifstream in(filename);
		if (!in.good()) return false;

		///only clear project if we found a good file to load
		out->ClearProject();

		std::string line;
		std::vector<std::string> lines;
		while (std::getline(in, line))
		{	
			if (line.size()) lines.push_back(RemoveWhitespaceAfter(line));
		}
		in.close();

		if (lines.size() == 0) return false;
		if (lines[0] != "Hercules:") return false;

		Node* t = new Node();
		t->key = StripNode(lines[0]);
		ParseNode(t, lines);
		ProcessResults(t, out);
		LoadingCleanup(t);
		return out;
	}

	std::string RemoveQuotes(std::string in)
	{
		in.erase(std::remove(in.begin(), in.end(), '\"'), in.end());
		return in;
	}

	size_t GetIndent(std::string in)
	{
		size_t c = 0;
		while (in.size() != 0 && in[0] == ' ')
		{
			c++;
			in.erase(in.begin());
		}
		return c;
	}

	bool IsItem(std::string in)
	{
		in = RemoveWhitespaceBefore(in);
		if (in.size() != 0 && in[0] == '-') return true; else return false;
	}

	bool IsNode(std::string in)
	{
		if (in.size() != 0 && in[in.size() - 1] == ':') return true; else return false;
	}

	std::string RemoveWhitespaceBefore(std::string in)
	{
		while (in.size() != 0 && in[0] == ' ') in.erase(in.begin());
		return in;
	}

	std::string RemoveWhitespaceAfter(std::string in)
	{
		while (in.size() != 0 && in[in.size() - 1] == ' ') in.erase(in.end() - 1);
		return in;
	}

	std::string StripItem(std::string in)
	{
		in = RemoveWhitespaceBefore(in);
		if (in.size() != 0 && in[0] == '-') in.erase(in.begin());
		in = RemoveWhitespaceBefore(in);
		return in;
	}

	std::string StripNode(std::string in)
	{
		in = RemoveWhitespaceBefore(in);
		if (in.size() != 0 && in[in.size() - 1] == ':') in.erase(in.end() - 1);
		return in;
	}

	void ParseNode(Node* current, std::vector<std::string> lines, size_t c)
	{
		if (lines.size() <= c) return;
		std::string scurrent = lines[c];
		c++;

		for (size_t counter = c; counter < lines.size(); counter++)
		{
			std::string i = lines[counter];
			if (GetIndent(i) == GetIndent(scurrent)) break;
			if (GetIndent(i) == (GetIndent(scurrent)) + 2)
			{
				if (IsNode(i))
				{
					Node* t = new Node();
					t->parent = current;
					t->key = StripNode(i);
					current->children.push_back(t);
					ParseNode(t, lines, counter);
				}
				else if (IsItem(i))
				{
					current->contents.push_back(StripItem(i));
				}
			}
		}
	}

	void ProcessResults(Node* current, Model * out)
	{
		std::string title;
		for (auto i : current->children)
		{
			if (i->key == "UMLObject")
			{
				title.clear();
				for (auto j : i->children)
				{
					if (j->key == "Title" && j->contents.size() == 1)
					{
						title = j->contents[0];
					}
				}
				if (title != "")
				{
					out->addClass(title);
					for (auto j : i->children)
					{
						if (j->key == "UMLField")
						{
							out->addField(title, FindChildWhere(j, "Name"), FindChildWhere(j, "Type"), VisibilityFromString(FindChildWhere(j, "Visibility")));
						}
						else if (j->key == "UMLMethod")
						{
							out->addMethod(title, FindChildWhere(j, "Name"), FindChildWhere(j, "Type"), VisibilityFromString(FindChildWhere(j, "Visibility")));
							if (FindNodesWhere(j, "Parameters").size() > 0)
							{
								Node* head = FindNodesWhere(j, "Parameters")[0];
								std::vector<Node*> tar = FindNodesWhere(head, "UMLParameter");
								for (auto i : tar)
								{
									out->addParameter(title, FindChildWhere(j, "Name"), FindChildWhere(i, "Name"), FindChildWhere(i, "Type"));
								}
								
							}
						}
						else if (j->key == "X")
						{
							out->SetX(title, std::stoi(j->contents[0]));
						}
						else if (j->key == "Y")
						{
							out->SetY(title, std::stoi(j->contents[0]));
						}
					}
				}
			}
			else if (i->key == "UMLRelationship")
			{
				out->addRelationship(FindChildWhere(i, "Parent"), FindChildWhere(i, "Child"), RelationshipFromString(FindChildWhere(i, "Type")));
			}
		}
	}

	std::string FindChildWhere(Node * in, std::string key)
	{
		std::string out;
		for (auto i : in->children)
		{
			if (i->key == key)
			{
				if (i->contents.size() == 1)
				{
					out = RemoveQuotes(i->contents[0]);
					break;
				}
			}
		}
		return out;
	}

	std::vector<Node*> FindNodesWhere(Node* in, std::string key)
	{
		std::vector<Node*> t;
		for (auto i : in->children)
		{
			if (i->key == key)
			{
				t.push_back(i);
			}
		}
		return t;
	}

	void LoadingCleanup(Node* in)
	{
		for (auto i : in->children)
		{
			LoadingCleanup(i);
		}
		delete (in);
	}
}
