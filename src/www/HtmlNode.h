#ifndef OTTERDICT_HTMLNODE_H_GUARD
#define OTTERDICT_HTMLNODE_H_GUARD

#include <string>
#include <map>

/**
 * Class representing one HTML node. This class is used as a building element
 * in the HtmlParser class. It's main goal is that the original HTML code
 * is left unmodified even during queries about the content. This could be
 * very useful when you are doing only minor changes to the HTML document
 * and you do not want to destroy the original formatting.
 *
 * When the node is a HTML tag, it is possible to retrieve values of its
 * attributes and set them as well. However, setting attributes will
 * cause reformatting of the element. See parseAttributes() and
 * unparseAttributes() for more details.
 *
 * This class was much inspired by the Node class of 
 * <a href="http://htmlcxx.sourceforge.net">htmlcxx library</a> but
 * provides extra functionality of setting attribute values back.
 * 
 * \section htmlnodenamingconventions Naming conventions
 * By opening and closing text is meant - depending on the node type
 * - text
 *   - opening - whole text
 *   - closing - empty
 * - comment
 *   - opening - whole comment (including comment delimiters)
 *   - closing - empty
 * - tag
 *   - opening - less than bracket, tag name, attributes and closing gt bracket
 *   - closing - closing tag (with brackets) or empty
 */
class HtmlNode {
	public:
		HtmlNode();
		HtmlNode(const std::string & tagname);
		HtmlNode(const std::string openingText, const std::string closingText);
		~HtmlNode();

		void setOpeningText(const std::string openingText);
		std::string getOpeningText() const;

		void setClosingText(const std::string closingText);
		std::string getClosingText() const;

		std::string getTagName(bool normalized = false) const;		

		bool isComment() const;
		void setComment();
		
		bool isTag() const;
		bool isTag(const char * tagname) const;
		void setTag();
		
		void setText();
		bool isText() const;

		void parseAttributes(bool normalizeAttributes = false);
		std::string getAttribute(std::string name);
		bool isAttributeSet(std::string name) const;
		void setAttribute(std::string name, std::string value);
		void unparseAttributes();
	private:
		enum Type {COMMENT, TAG, TEXT};
		std::string openingText_;
		std::string closingText_;
		std::string tagName_;
		typedef std::map<std::string, std::string> Attributes;
		Attributes attributes_;
		bool attributesParsed_;
		Type type;

}; // class HtmlNode

#endif
