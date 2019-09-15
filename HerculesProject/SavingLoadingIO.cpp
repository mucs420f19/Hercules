#include "SavingLoadingIO.h"

namespace SavingLoadingIO
{
	void SaveProjectToFile(std::vector<UMLObject*> in)
	{
		std::ofstream out("output.xml");
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

	std::vector<UMLObject*> LoadProject()
	{
		return std::vector<UMLObject*>();
	}
}
