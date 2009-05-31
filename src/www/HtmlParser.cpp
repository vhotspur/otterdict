#include <sstream>
#include <iostream>
#include <string>

#include "HtmlParser.h"

/**
 * Default constructor.
 * 
 */
HtmlParser::HtmlParser() :
	htmlTree_()
{}
	
/**
 * Destructor.
 * 
 */
HtmlParser::~HtmlParser() {
}

/**
 * Parses HTML code into a tree.
 * @param html HTML code to parse
 * 
 */
void HtmlParser::parseTree(const std::string & html) {
	this->parse(html);
}

/**
 * Returns HTML tree.
 * @return HTML tree
 * 
 */
HtmlParser::HtmlTree HtmlParser::getTree() const {
	return htmlTree_;
}

/**
 * Sets new HTML tree.
 * @param tree New tree holding HTML nodes
 * 
 */
void HtmlParser::setTree(const HtmlTree tree) {
	htmlTree_ = tree;
}

/**
 * Converts tree back to string. When no changes to the tree were
 * performed, the returned code is exactly the same as the one
 * passed to the parseTree() function.
 * @return HTML code
 * 
 */
std::string HtmlParser::toString() const {
	return toString(htmlTree_.begin());
}

/**
 * Initialization of the parser variables.
 * 
 */
void HtmlParser::beginParsing() {
	HtmlNode node("","");
	node.setTag();
	htmlTree_.clear();
	currentState_ = htmlTree_.insert(htmlTree_.begin(),node);
}

/**
 * Callback when tag was found.
 * @param node Already created HTML node
 * @param isEnd Whether we found end tag
 * 
 */
void HtmlParser::foundTag(HtmlNode hnode, bool isEnd) {
	if (!isEnd) {
		HtmlTree::iterator tmp = htmlTree_.append_child(currentState_,hnode);
		currentState_ = tmp;
	} else {
		/*
		 * it is a closing tag - we will climb up the tree until we 
		 * have found an opening tag with the same name
		 * afterwards, we would make all nodes between direct childs
		 * of this node (tree flattening)
		 * in case no such opening tag would be found we would make comment
		 * out of this tag
		 * 
		 */		
		HtmlTree::iterator top = htmlTree_.begin(); // stopper for the climb
		HtmlTree::iterator climber = currentState_; // use this to climb up
		
		const char * currentTag = hnode.getTagName().c_str();
		bool foundOpened = false;
		while (climber != top) {
			const char * climberTag = climber->getTagName().c_str();
			if (strcasecmp(climberTag,currentTag) == 0) {
				// found the closing tag
				foundOpened = true;
				break;
			}
			climber = htmlTree_.parent(climber);
		}
		
		if (foundOpened) {
			// do some flattening
			currentState_ = htmlTree_.parent(climber);
			climber->setClosingText(hnode.getOpeningText());
			// FIXME on implicit closings
		} else {
			hnode.setComment();
			htmlTree_.append_child(currentState_,hnode);
		}
	}
}

/**
 * Callback when text was found.
 * @param node Already created HTML node
 * 
 */
void HtmlParser::foundText(HtmlNode hnode) {
	htmlTree_.append_child(currentState_,hnode);
}

/**
 * Callback when comment was found.
 * @param node Already created HTML node
 * 
 */
void HtmlParser::foundComment(HtmlNode hnode) {
	htmlTree_.append_child(currentState_,hnode);
}

/**
 * Cleanup after parsing.
 * 
 */
void HtmlParser::endParsing() {	
	//std::cerr << dump() << std::endl;
}

/**
 * Dumps the HTML tree in indented form. This function is useful only
 * for debugging and shall not be used in production code.
 * @return Tree dump
 *
 */
std::string HtmlParser::dump() const {
	HtmlTree::pre_order_iterator it = htmlTree_.begin();
	HtmlTree::pre_order_iterator itEnd = htmlTree_.end();
	
	std::stringstream contents("");
	
	for (int i=0; it != itEnd; ++it, i++) {
		for (int j=0; j<htmlTree_.depth(it); j++) contents << " ";
					
		contents << "'";
		std::string t = it->getOpeningText();
		std::string::size_type pos;
		while ((pos = t.find("\n")) != std::string::npos) {
			t.replace(pos,1,"\\");
			t.insert(pos+1,"n");
		}
		contents << t << "' (" << it->getClosingText() << ")" << std::endl;
	}
	
	return contents.str();
}

/**
 * Converter from subtree to string. 
 * @param subtree Iterator to the pseudo root of the tree
 * @return HTML code of the sub tree
 * 
 */
std::string HtmlParser::toString(HtmlTree::iterator subtree) const {
	std::string result("");
	
	result.append(subtree->getOpeningText());
	if (subtree->isTag()) {		
		HtmlTree::sibling_iterator lastChild = htmlTree_.end(subtree);
		for (HtmlTree::sibling_iterator it = htmlTree_.begin(subtree); it != lastChild; ++it) {
			result.append(toString(it));
		}
		result.append(subtree->getClosingText());
	}
	
	return result;
}

