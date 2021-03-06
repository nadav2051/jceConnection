#include "Page.h"

Page::Page(string& html)
{
	cout << "bulding page... string size: " << html.length() << endl;
	if(html.empty())
		cout << "ERROR: unable to build Page" << endl;
	makeText(html);
}

Page::~Page()
{
	cout << "killing Page..." <<endl;
}

void Page::makeText(string& html)
{
	bool foundTitle = false;
	bool inBody = false;
	string temp = "";
	for (int i = 0; i < html.length() ; i++)
	{
		if(!foundTitle)
		{
			if(html[i] == '<')
			{
				//title>
				i++;
				string titleTag = html.substr(i, 5); //legth of title
				if(titleTag == "title") //check if the tag is title
				{
					while(html[i] != '>')
						i++;
					i++;
					while(html[i] != '<')
					{
						temp += html[i];
						i++;
					}
					foundTitle = true;
					this->title = temp;
				}
			}
			temp = "" ; //clear temp BUFFER
		}
		else
		{
			if(html[i] == '<')
			{
				//body>
				i++;
				string bodyTag = html.substr(i, 4); //legth of "body"
				if(bodyTag == "body") //check if the tag is body tag
				{
					while(html[i] != '>')
						i++;
					inBody = true;
				}
			}
		}
		
		/**
		 * Actual Body Text In String
		 */
		 if(inBody)
		 {
		 	if(html[i] == '<')
		 	{
				//tr> / td>
		 		i++;
				string tableTag = html.substr(i, 2); //legth of "tr/td"
				if(tableTag == "tr")
				{
					temp += "\n"; //new row -> new line
					while(html[i] != '>')
						i++;
					i++;
				}
				else if(tableTag == "td")
				{
					temp += "\t"; // new cell -> tab between data	
					while(html[i] != '>')
						i++;
					i++;
				}
			}
			if(html[i] == '>')
			{
				i++;
				if(endOfString(i, html.length()))
					goto finishBuild; //Cheak if EOF (Text)
				while(html[i] != '<')
				{
					if(endOfString(i, html.length()))
						goto finishBuild; //Cheak if EOF (Text)
					if(html[i] == '&')
					{
					//&nbsp;
						string nbspChr = html.substr(i, 6);
						if(nbspChr == "&nbsp;")
						i += 6;
						if(endOfString(i, html.length()))
							goto finishBuild; //Cheak if EOF (Text)
					}
					if(html[i] == '<')
						continue;
					else if(html[i] != '\n')
						temp += html[i];
					i++;
				}
			}
		}
	}
	finishBuild:
		this->text = temp;
}

bool Page::endOfString(int index, int length)
{
	if(index < length)
		return false;
	return true;
}

string Page::getString()
{
	return this->text;
}

string Page::getTitle()
{
	return this->title;
}