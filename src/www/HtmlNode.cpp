#include <iostream>
#include <strings.h>
#include <string.h>

#include "HtmlNode.h"

/**
 * Default constructor, creates empty text node.
 * 
 */
HtmlNode::HtmlNode() :
	openingText_(""),
    closingText_(""),
	tagName_(""),
	attributesParsed_(false),
	type(TEXT)
{}

/**
 * Constructor setting tag name.
 * 
 * @param tagname Tag name (without angle brackets)
 * 
 */
HtmlNode::HtmlNode(const std::string & tagname) :
	openingText_(""),
	closingText_(""),
	tagName_(tagname),
	attributesParsed_(false),
	type(TAG)
{}

/**
 * Constructor, creates HTML tag node.
 * @param openingText Tag opening
 * @param closingText Tag closing
 * 
 */
HtmlNode::HtmlNode(const std::string openingText, const std::string closingText) :
	openingText_(openingText),
	closingText_(closingText),
	tagName_(openingText),
	attributesParsed_(false),
	type(TAG)
{}


/**
 * Destructor, currently does nothing
 * 
 */
HtmlNode::~HtmlNode() {
	
}

/**
 * Sets opening text.
 * @param openingText New opening text
 * 
 */
void HtmlNode::setOpeningText(const std::string openingText) {	
	openingText_ = openingText;
}

/**
 * Tells opening text of the node.
 * @return Opening text
 * 
 */
std::string HtmlNode::getOpeningText() const {
	return openingText_;
}

/**
 * Sets closing text.
 * @param closingText New closing text
 * @warning This text comes in effect only when node type is tag.
 * 
 */
void HtmlNode::setClosingText(const std::string closingText) {	
	closingText_ = closingText;
}

/**
 * Tells closing text of the node.
 * @return Closing text
 * @warning When node type is different from tag, return value is unspecified
 * 
 */
std::string HtmlNode::getClosingText() const {
	return closingText_;
}

/**
 * Tells tag name.
 * @param normalized Whether to normalize (downcase) the name
 * @return Tag name
 * @warning When node type is different from tag, return value is unspecified
 * 
 */
std::string HtmlNode::getTagName(bool normalized) const {
	// FIXME - normalizing not done
	return tagName_;
}

/**
 * Sets node type to comment.
 * 
 */
void HtmlNode::setComment() {
	type = COMMENT;
}

/**
 * Tells whether node is a comment.
 * 
 */
bool HtmlNode::isComment() const {
	return type == COMMENT;
}

/**
 * Tells whether node is a tag.
 * 
 */
bool HtmlNode::isTag() const {
	return type == TAG;
}

/**
 * Tells whether node is a tag with given name.
 * @param tagname Tag name
 * @retval true Node is tag and has given tagname
 * @retval false Type of the node is not tag or tag has different name
 * 
 * @warning Comparison is done case insensitively.
 */
bool HtmlNode::isTag(const char * tagname) const {
	return isTag() && (strcasecmp(tagname, tagName_.c_str()) == 0);
}

/**
 * Sets node type to tag.
 * 
 */
void HtmlNode::setTag() {
	type = TAG;
}

void HtmlNode::setText() {
	type = TEXT;
}

bool HtmlNode::isText() const {
	return type == TEXT;
}

/**
 * Parses attributes from opening text of the tag. This function does nothing
 * when node type is different from tag. The parser tries to be as tolerant
 * as possible (unquoted attribute values, extra spaces ...). When attribute
 * with no value is found (common in HTML, not in XHTML), its value is set
 * to its name (to ensure forward compatibility - e.g. in option tag it is
 * common to use <code>selected="selected"</code> in XHTML instead of
 * <code>selected</code> in HTML).
 * 
 */
void HtmlNode::parseAttributes(bool normalizeAttributes) {
	#define SKIPSPACE(ptr) while (isspace(*ptr)) ptr++
	if (type != TAG) {
		return;
	}
	
	if (attributesParsed_) {
		return;
	}
	
	const char *ptr = openingText_.c_str();
	if ((ptr = strchr(ptr, '<')) == 0) {
		return; // no <, probably something weird is going on...
	}
	ptr++;
	SKIPSPACE(ptr);
	
	// here shall be the tag name (which shall be skipped
	// as well as following blanks
	if (!isalpha(*ptr)) {
		return;
	}
	while (isalnum(*ptr)) {
		ptr++;
	}
	SKIPSPACE(ptr);
		
	// iterate through attributes
	while (*ptr && (*ptr != '>')) {
		const char * attrStart;
	
		// skip garbage before attribute name
		while (*ptr && !isalpha(*ptr)) {
			ptr++;
		}		
		if (*ptr == 0) {
			return;
		}
		
		// read in attribute name
		attrStart = ptr++;
		while (*ptr && (isalnum(*ptr) || (*ptr == '-'))) {
			ptr++;
		}
		if (*ptr == 0) {
			return;
		}
		std::string key(attrStart, ptr - attrStart);
		
		// skip '=' and spaces
		bool foundAssign = false;
		while (*ptr && (isspace(*ptr) || ((*ptr == '=') && (foundAssign=true)))) {
			ptr++;
		}
		if (*ptr == 0) {
			return;
		}
		
		// find the attribute value
		std::string val;
		if (!foundAssign) {
			// attribute without value
			// by this we somehow ensure compatibility (fingers crossed)
			// FIXME - how about extra parameter for this
			val = key;
		} else {
			char quitchar = 0;
			const char * start;
			if ((*ptr == '"') || (*ptr == '\'')) {
				quitchar = *ptr;
				start = ++ptr;
			} else {
				start = ptr;
			}
			// FIXME - how is it with escaped quotes?
			while (*ptr && (
					((quitchar == 0) && (!isspace(*ptr))) ||
					(quitchar && (*ptr != quitchar))
				)) {
				ptr++;
			}
			if (*ptr == 0) {
				return;
			}
			val = std::string(start, ptr - start);
			ptr++; //skip the space or the quote
		}
		
		// normalize (attribute name to lower case)
		if (normalizeAttributes) {
			// transform would be ideal here, thought it may not be
			// portable, so let's do it the ugly way
			// (see http://bytes.com/groups/c/60652-tolower-used-transform)
			std::string::iterator e = key.end();
			for (std::string::iterator it = key.begin(); it != e; ++it) {
				*it = tolower(*it);
			}
		}
				
		// store the attribute
		attributes_[key] = val;
	}
	
	attributesParsed_ = true;
	#undef SKIPSPACE
}

/**
 * Tells attribute value.
 * @param name Attribute name
 * @return Attribute value
 * 
 * @warning When node type is not tag, result is unpredictable.
 * 
 * @warning When given attribute does not exist, empty string is
 * returned (to check for existence, use isAttributeSet().
 * 
 */
std::string HtmlNode::getAttribute(std::string name) {
	Attributes::iterator it = attributes_.find(name);
	if (it != attributes_.end()) {
		return it->second;		
	} else {
		return std::string("");
	}
}

/**
 * Tells whether attribute value is set.
 * @param name Attribute name
 * @return Whether attribute is set
 * 
 * @warning When node type is not tag, result is unpredictable.
 * 
 */
bool HtmlNode::isAttributeSet(std::string name) const {
	return attributes_.find(name) != attributes_.end();
}

/**
 * Sets new value for an attribute.
 * @param name Attribute name
 * @param value Attribute value
 * 
 * @warning When node type is not tag, result is unpredictable.
 * 
 */
void HtmlNode::setAttribute(std::string name, std::string value) {
	attributes_[name] = value;
}

/**
 * Creates new opening text from current attributes. This function scans
 * all parsed attributes (that includes newly added ones created through
 * setAttribute() call) and creates new opening text (including the tag
 * name and braces, of course); attributes are separated by single
 * space and all values are double-qouted.
 * 
 */
void HtmlNode::unparseAttributes() {
	if (!isTag()) {
		return;
	}
	
	std::string opening("<");
	opening.append(getTagName());
	
	
	Attributes::iterator e = attributes_.end();
	for (Attributes::iterator it = attributes_.begin(); it != e; ++it) {
		// FIXME - this shall be done nicer (somehow)
		opening.append(" ");
		opening.append(it->first);
		opening.append("=\"");
		opening.append(it->second);
		opening.append("\"");
    }
	
	//FIXME - add /> on empty tags
	opening.append(">");
	openingText_ = opening;
}

