#ifndef OTTERDICT_HTMLPARSER_H_GUARD
#define OTTERDICT_HTMLPARSER_H_GUARD

#include <string>
#include "ParserSax.h"
#include "HtmlNode.h"
#include "tree.h"


/**
 * Simple HTML parser. This parser is much inspired by the ParserDom class
 * of <a href="http://htmlcxx.sourceforge.net">htmlcxx library</a> but
 * uses HtmlNode class to store node info.
 * 
 */
class HtmlParser : public ParserSax {
	public:
		HtmlParser();
		virtual ~HtmlParser();
		
		typedef tree< HtmlNode > HtmlTree;
		
		void parseTree(const std::string & html);
		HtmlTree getTree() const;
		void setTree(const HtmlTree tree);
		
		std::string dump() const;
		std::string toString() const;
	protected:
		std::string toString(HtmlTree::iterator subtree) const;
		virtual void beginParsing();

		virtual void foundTag(HtmlNode hnode, bool isEnd);
		virtual void foundText(HtmlNode hnode);
		virtual void foundComment(HtmlNode hnode);

		virtual void endParsing();
	private:
		HtmlTree htmlTree_;
		HtmlTree::iterator currentState_;
}; // class HtmlParser


#endif
