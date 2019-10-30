#include "SavingLoadingIO.h"

namespace SavingLoadingIO
{
	int SaveProjectToFile(UMLObjectsHolder* in, std::string filename, bool overwrite)
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

		for (auto i : in->ReturnPtrToVector())
		{
			out << "  UMLObject:\n";
			out << "    Title:\n";
			out << "      - " << i->ReturnTitle() << "\n";
			for (auto j : i->ReturnFieldsRaw())
			{
				out << "    UMLField:\n";

				out << "      Name:\n";
				out << "        - " << j.ReturnName() << "\n";

				out << "      Type:\n";
				out << "        - " << j.ReturnType() << "\n";

				out << "      Visibility:\n";
				out << "        - " << j.ReturnVisibility() << "\n";
			}

			for (auto j : i->ReturnMethodsRaw())
			{
				out << "    UMLMethod:\n";

				out << "      Name:\n";
				out << "        - " << j.ReturnName() << "\n";

				out << "      Type:\n";
				out << "        - " << j.ReturnType() << "\n";

				out << "      Visibility:\n";
				out << "        - " << j.ReturnVisibility() << "\n";

				out << "      Parameters:\n";

				for (auto k : j.ReturnParametersRaw())
				{
					out << "        UMLParameter:\n";

					out << "          Type:\n";
					out << "            - " << k.ReturnType()<< "\n";

					out << "          Name:\n";
					out << "            - " << k.ReturnName() << "\n";

					out << "          Optional:\n";
					out << "            - " << k.ReturnOpt() << "\n";

					out << "          Default:\n";
					out << "            - " << k.ReturnDefault() << "\n";
				}
			}

			for (auto j : i->ReturnRelationshipsRaw())
			{
				out << "    UMLRelationship:\n";

				out << "      Object:\n";
				out << "        - " << j.GetObject() << "\n";

				out << "      Type:\n";
				out << "        - " << j.type << "\n";

				out << "      Quantifier:\n";
				out << "        - " << j.quantifier << "\n";
			}
		}
		out.close();
		return SaveSuccess;
	}

	bool LoadProject(UMLObjectsHolder* out, std::string filename)
	{
		out->ClearProject();
		std::ifstream in(filename);
		if (!in.good()) return false;

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
		std::vector<Relationship> rela;
		ProcessResults(t, out, rela);
		for (auto i : rela)
		{
			out->GetUMLObject(i.parent)->AddRelationship({ std::stoi(i.type), std::stoi(i.quantifier), out->GetUMLObject(i.child), out->GetUMLObject(i.parent) });
		}
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

	void ProcessResults(Node* current, UMLObjectsHolder* out, std::vector<Relationship>& relationships)
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
					UMLObject* a = new UMLObject();
					a->SetTitle(title);
					out->AddUMLObject(a);
					for (auto j : i->children)
					{
						if (j->key == "UMLField")
						{
							UMLField field(FindChildWhere(j, "Name"), FindChildWhere(j, "Type"), FindChildWhere(j, "Visibility"));
							a->AddField(field);
						}
						else if (j->key == "UMLMethod")
						{
							std::vector<UMLParameter> params;
							if (FindNodesWhere(j, "Parameters").size() > 0)
							{
								Node* head = FindNodesWhere(j, "Parameters")[0];
								std::vector<Node*> tar = FindNodesWhere(head, "UMLParameter");
								for (auto i : tar)
								{
									UMLParameter param(FindChildWhere(i, "Type"), FindChildWhere(i, "Name"), FindChildWhere(i, "Optional"), FindChildWhere(i, "Default"));
									params.push_back(param);
								}
								
							}
							UMLMethod method(FindChildWhere(j, "Name"), FindChildWhere(j, "Type"), params, FindChildWhere(j, "Visibility"));
							a->AddMethod(method);
						}
						else if (j->key == "UMLRelationship")
						{
							relationships.push_back(Relationship(title, FindChildWhere(j, "Object"), FindChildWhere(j, "Type"), FindChildWhere(j, "Quantifier")));
						}
					}
				}
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
					out = i->contents[0];
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
