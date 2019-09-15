#include "SavingLoadingIO.h"

namespace SavingLoadingIO
{
	void SaveProjectToFile(std::vector<UMLObject*> in)
	{
		std::ofstream out(DefaultFileName);
		out << "<HerculesProject>\n";
		for (auto i : in)
		{
			out << "<UMLObject>\n";
			out << "<Title>\n";
			out << "\"" << i->ReturnTitle() << "\"\n";
			out << "</Title>\n";
			out << "<Fields>\n";
			for (auto j : i->ReturnFieldsRaw())
			{
				out << "<UMLField>\n";

				out << "<Name>\n";
				out << "\"" << j.ReturnName() << "\"\n";
				out << "</Name>\n";

				out << "<Type>\n";
				out << "\"" << j.ReturnType() << "\"\n";
				out << "</Type>\n";

				out << "<Visibility>\n";
				out  << j.ReturnVisibility() << "\n";
				out << "</Visibility>\n";

				out << "</UMLField>\n";
			}
			out << "</Fields>\n";
			out << "<Methods>\n";
			for (auto j : i->ReturnMethodsRaw())
			{
				out << "<UMLMethod>\n";

				out << "<Name>\n";
				out << "\"" << j.ReturnName() << "\"\n";
				out << "</Name>\n";

				out << "<Type>\n";
				out << "\"" << j.ReturnType() << "\"\n";
				out << "</Type>\n";

				out << "<Visibility>\n";
				out << j.ReturnVisibility() << "\n";
				out << "</Visibility>\n";

				out << "<Parameters>\n";

				for (auto k : j.ReturnParameters())
				{
					out << "<Parameter>\n";
					out << "\"" << k << "\"\n";
					out << "</Parameter>\n";
				}

				out << "</Parameters>\n";

				out << "</UMLMethod>\n";
			}
			out << "</Methods>\n";
			out << "</UMLObject>\n";
		}
		out << "</HerculesProject>";
		out.close();
	}

	std::vector<UMLObject*> LoadProject(std::string filename)
	{
		std::ifstream in(filename);
		std::vector<UMLObject*> out;
		//check for errors
		
		std::string line;
		std::vector<std::string> lines;
		while (std::getline(in, line))
		{
			while (line[0] == ' ') line.erase(line.begin(), line.begin() + 1);
			lines.push_back(line);
		}

		//invalid file
		if (lines[0] != "<HerculesProject>" && lines[lines.size() - 1] != "</HerculesProject>") return out;
		lines.erase(lines.begin(), lines.begin() + 1);
		lines.erase(lines.end() - 1, lines.end());


		size_t s1, s2, t1, t2;

		while (lines.size())
		{

			s1 = -1;
			s2 = -1;
			for (size_t i = 0; i < lines.size(); i++)
			{
				t1 = lines[i].find("<UMLObject>");
				if (t1 != std::string::npos)
				{
					s1 = i;
				}
				t2 = lines[i].find("</UMLObject>");
				if (t2 != std::string::npos)
				{
					s2 = i;
				}
				if (s1 != -1 && s2 != -1)
				{
					break;
				}
			}

			//something is mismatched
			if (s1 == std::string::npos || s2 == std::string::npos) return out;

			std::vector<std::string> i1;
			std::copy(lines.begin() + s1, lines.begin() + s2 + 1, std::back_inserter(i1));
			lines.erase(lines.begin() + s1, lines.begin() + s2 + 1);

			out.push_back(ProcessUMLObject(i1));

		}



		return out;
	}

	std::string RemoveQuotes(std::string in)
	{
		in.erase(std::remove(in.begin(), in.end(), '\"'), in.end());
		return in;
	}

	UMLObject* ProcessUMLObject(std::vector<std::string> i1)
	{
		if (i1[0] != "<UMLObject>" || i1[i1.size() - 1] != "</UMLObject>") return 0;
		//process i1
		i1.erase(i1.begin(), i1.begin() + 1);
		i1.erase(i1.end() - 1, i1.end());

		UMLObject* a = new UMLObject();

		size_t s1, s2, t1, t2;

		s1 = -1;
		s2 = -1;
		for (size_t i = 0; i < i1.size(); i++)
		{
			t1 = i1[i].find("<Title>");
			if (t1 != std::string::npos)
			{
				s1 = i;
			}
			t2 = i1[i].find("</Title>");
			if (t2 != std::string::npos)
			{
				s2 = i;
			}
			if (s1 != -1 && s2 != -1)
			{
				break;
			}
		}

		a->SetTitle(RemoveQuotes(i1[s1 + 1]));

		while (i1.size())
		{

			s1 = -1;
			s2 = -1;
			for (size_t i = 0; i < i1.size(); i++)
			{
				t1 = i1[i].find("<UMLField>");
				if (t1 != std::string::npos)
				{
					s1 = i;
				}
				t2 = i1[i].find("</UMLField>");
				if (t2 != std::string::npos)
				{
					s2 = i;
				}
				if (s1 != -1 && s2 != -1)
				{
					break;
				}
			}

			//something is mismatched
			if (s1 == std::string::npos || s2 == std::string::npos) break;

			std::vector<std::string> i2;
			std::copy(i1.begin() + s1, i1.begin() + s2 + 1, std::back_inserter(i2));
			i1.erase(i1.begin() + s1, i1.begin() + s2 + 1);

			ProcessUMLField(i2, a);

		}

		while (i1.size())
		{

			s1 = -1;
			s2 = -1;
			for (size_t i = 0; i < i1.size(); i++)
			{
				t1 = i1[i].find("<UMLMethod>");
				if (t1 != std::string::npos)
				{
					s1 = i;
				}
				t2 = i1[i].find("</UMLMethod>");
				if (t2 != std::string::npos)
				{
					s2 = i;
				}
				if (s1 != -1 && s2 != -1)
				{
					break;
				}
			}

			//something is mismatched
			if (s1 == std::string::npos || s2 == std::string::npos) break;

			std::vector<std::string> i2;
			std::copy(i1.begin() + s1, i1.begin() + s2 + 1, std::back_inserter(i2));
			i1.erase(i1.begin() + s1, i1.begin() + s2 + 1);

			ProcessUMLMethod(i2, a);

		}


		return a;
	}

	void ProcessUMLField(std::vector<std::string> i1, UMLObject* a)
	{
		size_t s1 = 0, s2 = i1.size(), t1, t2;
		UMLField b;

		while (s1 != s2)
		{
			std::string acc1 = i1[s1];
			if (acc1 == "<Name>")
			{
				b.SetName(RemoveQuotes(i1[s1 + 1]));
				s1 += 3;
			}
			else if (acc1 == "<Type>")
			{
				b.SetReturnType(RemoveQuotes(i1[s1 + 1]));
				s1 += 3;
			}
			else if (acc1 == "<Visibility>")
			{
				b.SetVisibility(std::stoi(i1[s1 + 1]));
				s1 += 3;
			}
			else s1++;
		}
		a->AddField(b);
	}

	void ProcessUMLMethod(std::vector<std::string> i1, UMLObject* a)
	{
		size_t s1 = 0, s2 = i1.size(), t1, t2;
		UMLMethod b;

		while (s1 != s2)
		{
			std::string acc1 = i1[s1];
			if (acc1 == "<Name>")
			{
				b.SetName(RemoveQuotes(i1[s1 + 1]));
				s1 += 3;
			}
			else if (acc1 == "<Type>")
			{
				b.SetReturnType(RemoveQuotes(i1[s1 + 1]));
				s1 += 3;
			}
			else if (acc1 == "<Visibility>")
			{
				b.SetVisibility(std::stoi(i1[s1 + 1]));
				s1 += 3;
			}
			else if (acc1 == "<Parameters>")
			{
				while (i1.size())
				{

					s1 = -1;
					s2 = -1;
					for (size_t i = 0; i < i1.size(); i++)
					{
						t1 = i1[i].find("<Parameters>");
						if (t1 != std::string::npos)
						{
							s1 = i;
						}
						t2 = i1[i].find("</Parameters>");
						if (t2 != std::string::npos)
						{
							s2 = i;
						}
						if (s1 != -1 && s2 != -1)
						{
							break;
						}
					}

					//something is mismatched
					if (s1 == std::string::npos || s2 == std::string::npos) break;

					std::vector<std::string> i2;
					std::copy(i1.begin() + s1, i1.begin() + s2 + 1, std::back_inserter(i2));
					i1.erase(i1.begin() + s1, i1.begin() + s2 + 1);

					ProcessUMLMethodParameters(i2, &b);

				}
			}
			else s1++;
		}
		a->AddMethod(b);
	}

	void ProcessUMLMethodParameters(std::vector<std::string> i1, UMLMethod* a)
	{
		size_t s1 = 0, s2 = i1.size(), t1, t2;
		std::vector<std::string> b;

		while (s1 != s2)
		{
			std::string acc1 = i1[s1];
			if (acc1 == "<Parameter>")
			{
				b.push_back(RemoveQuotes(i1[s1 + 1]));
				s1 += 3;
			}
			else s1++;
		}
		a->SetParameters(b);
	}
}
