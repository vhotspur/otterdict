#ifndef OTTERDICT_PARSERSAX_H_GUARD
#define OTTERDICT_PARSERSAX_H_GUARD

#include <string>
#include <strings.h>
#include <string.h>

#include "HtmlNode.h"

/**
 * Simple Sax parser. This parser is partially rewritten ParserSax of the
 * of <a href="http://htmlcxx.sourceforge.net">htmlcxx library</a> but
 * uses HtmlNode class to store node info.
 * 
 */
class ParserSax {
public:
	ParserSax() : mpLiteral(0), mCdata(false) {}
	virtual ~ParserSax() {}

	/** Parse the html code */
	void parse(const std::string &html) {parse(html.c_str(), html.c_str() + html.length());}

	template <typename _Iterator>
	void parse(_Iterator begin, _Iterator end);

protected:
	// Redefine this if you want to do some initialization before
	// the parsing
	virtual void beginParsing() {}

	virtual void foundTag(HtmlNode node, bool isEnd) = 0;
	virtual void foundText(HtmlNode node) = 0;
	virtual void foundComment(HtmlNode node) = 0;

	virtual void endParsing() {}


	template <typename _Iterator>
	void parse(_Iterator &begin, _Iterator &end,
			std::forward_iterator_tag);

	template <typename _Iterator>
	void parseHtmlTag(_Iterator b, _Iterator c);

	template <typename _Iterator>
	void parseContent(_Iterator b, _Iterator c);

	template <typename _Iterator>
	void parseComment(_Iterator b, _Iterator c);

	template <typename _Iterator>
	_Iterator skipHtmlTag(_Iterator ptr, _Iterator end);
	
	template <typename _Iterator>
	_Iterator skipHtmlComment(_Iterator ptr, _Iterator end);

	unsigned long mCurrentOffset;
	const char *mpLiteral;
	bool mCdata;
}; // class ParserSax

#include <cctype>

static
struct literal_tag {
	int len;
	const char * str;
	int is_cdata;
}   
literal_mode_elem[] =
{   
	{6, "script", 1},
	{5, "style", 1},
	{3, "xmp", 1},
	{9, "plaintext", 1},
	{8, "textarea", 0},
	{0, 0, 0}
};

template <typename _Iterator>
void ParserSax::parse(_Iterator begin, _Iterator end)
{
	parse(begin, end, typename std::iterator_traits<_Iterator>::iterator_category());
}

template <typename _Iterator>
void ParserSax::parse(_Iterator &begin, _Iterator &end, std::forward_iterator_tag)
{
	typedef _Iterator iterator;
	mCdata = false;
	mpLiteral = 0;
	mCurrentOffset = 0;
	this->beginParsing();

	while (begin != end)
	{
		//*begin; // This is for the multi_pass to release the buffer
		iterator c(begin);

		while (c != end)
		{
			// For some tags, the text inside it is considered literal and is
			// only closed for its </TAG> counterpart
			while (mpLiteral)
			{
				while (c != end && *c != '<') ++c;

				if (c == end) {
					if (c != begin) this->parseContent(begin, c);
					goto DONE;
				}

				iterator end_text(c);
				++c;

				if (*c == '/')
				{
					++c;
					const char *l = mpLiteral;
					while (*l && ::tolower(*c) == *l)
					{
						++c;
						++l;
					}

					// FIXME: Mozilla stops when it sees a /plaintext. Check
					// other browsers and decide what to do
					if (!*l && strcmp(mpLiteral, "plaintext"))
					{
						// matched all and is not tag plaintext
						while (isspace(*c)) ++c;

						if (*c == '>')
						{
							++c;
							if (begin != end_text)
								this->parseContent(begin, end_text);
							mpLiteral = 0;
							c = end_text;
							begin = c;
							break;
						}
					}
				}
				else if (*c == '!')
				{
					// we may find a comment and we should support it
					iterator e(c);
					++e;

					if (e != end && *e == '-' && ++e != end && *e == '-')
					{
						++e;
						c = this->skipHtmlComment(e, end);
					}
				}
			}

			if (*c == '<')
			{
				iterator d(c);
				++d;
				if (d != end)
				{
					if (isalpha(*d))
					{
						// beginning of tag
						if (begin != c)
							this->parseContent(begin, c);

						d = this->skipHtmlTag(d, end);
						this->parseHtmlTag(c, d);

						// continue from the end of the tag
						c = d;
						begin = c;
						break;
					}

					if (*d == '/')
					{
						if (begin != c)
							this->parseContent(begin, c);

						iterator e(d);
						++e;
						if (e != end && isalpha(*e))
						{
							// end of tag
							d = this->skipHtmlTag(d, end);
							this->parseHtmlTag(c, d);
						}
						else
						{
							// not a conforming end of tag, treat as comment
							// as Mozilla does
							d = this->skipHtmlTag(d, end);
							this->parseComment(c, d);
						}

						// continue from the end of the tag
						c = d;
						begin = c;
						break;
					}

					if (*d == '!')
					{
						// comment
						if (begin != c)
							this->parseContent(begin, c);

						iterator e(d);
						++e;

						if (e != end && *e == '-' && ++e != end && *e == '-')
						{
							++e;
							d = this->skipHtmlComment(e, end);
						}
						else
						{
							d = this->skipHtmlTag(d, end);
						}

						this->parseComment(c, d);

						// continue from the end of the comment
						c = d;
						begin = c;
						break;
					}

					if (*d == '?' || *d == '%')
					{
						// something like <?xml or <%VBSCRIPT
						if (begin != c)
							this->parseContent(begin, c);

						d = this->skipHtmlTag(d, end);

						this->parseComment(c, d);

						// continue from the end of the comment
						c = d;
						begin = c;
						break;
					}
				}
			}
			c++;
		}

		// There may be some text in the end of the document
		if (begin != c)
		{
			this->parseContent(begin, c);
			begin = c;
		}
	}

DONE:
	this->endParsing();
	return;
}

template <typename _Iterator>
void ParserSax::parseComment(_Iterator b, _Iterator c)
{
	//FIXME: set_tagname shouldn't be needed, but first I must check
	//legacy code
	std::string comment(b, c);
	HtmlNode com_node(comment);
	com_node.setOpeningText(comment);
	com_node.setComment();

	mCurrentOffset += comment.length();

	// Call callback method
	this->foundComment(com_node);
}

template <typename _Iterator>
void ParserSax::parseContent(_Iterator b, _Iterator c)
{
	//FIXME: set_tagname shouldn't be needed, but first I must check
	//legacy code
	std::string text(b, c);
	HtmlNode txt_node(text, "");
	txt_node.setText();
	
	mCurrentOffset += text.length();

	// Call callback method
	this->foundText(txt_node);
}

template <typename _Iterator>
void ParserSax::parseHtmlTag(_Iterator b, _Iterator c)
{
	_Iterator name_begin(b);
	++name_begin;
	bool is_end_tag = (*name_begin == '/');
	if (is_end_tag) ++name_begin;

	_Iterator name_end(name_begin);
	while (name_end != c && isalnum(*name_end)) 
	{
		++name_end;
	}

	std::string name(name_begin, name_end);

	if (!is_end_tag) 
	{
		std::string::size_type tag_len = name.length();
		for (int i = 0; literal_mode_elem[i].len; ++i)
		{
			if ((int)tag_len == literal_mode_elem[i].len)
			{
				#ifdef WIN32
				if (!_stricmp(name.c_str(), literal_mode_elem[i].str))
				#else
				if (!strcasecmp(name.c_str(), literal_mode_elem[i].str))
				#endif
				{
					mpLiteral = literal_mode_elem[i].str;
					break;
				}
			}
		}
	} 

	//by now, length is just the size of the tag
	std::string text(b, c);
	HtmlNode tag_node(name);
	tag_node.setOpeningText(text);

	mCurrentOffset += text.length();

	this->foundTag(tag_node, is_end_tag);
}

template <typename _Iterator>
_Iterator
ParserSax::skipHtmlComment(_Iterator c, _Iterator end)
{
	while ( c != end ) {
		if (*c++ == '-' && c != end && *c == '-')
		{
			_Iterator d(c);
			while (++c != end && isspace(*c));
			if (c == end || *c++ == '>') break;
			c = d;
		}
	}

	return c;
}


template <typename _Iterator>
static inline
_Iterator find_next_quote(_Iterator c, _Iterator end, char quote)
{
	while (c != end && *c != quote) ++c;
	return c;
}

template <>
const char *find_next_quote(const char *c, const char *end, char quote)
{
	const char *d = reinterpret_cast<const char*>(memchr(c, quote, end - c));

	if (d) return d;
	else return end;
}



template <typename _Iterator>
_Iterator ParserSax::skipHtmlTag(_Iterator c, _Iterator end)
{
	while (c != end && *c != '>')
	{
		if (*c != '=') 
		{
			++c;
		}
		else
		{ // found an attribute
			++c;
			while (c != end && isspace(*c)) ++c;

			if (c == end) break;

			if (*c == '\"' || *c == '\'') 
			{
				_Iterator save(c);
				char quote = *c++;
				c = find_next_quote(c, end, quote);
				if (c != end) 
				{
					++c;
				} 
				else 
				{
					c = save;
					++c;
				}
			}
		}
	}

	if (c != end) ++c;
	
	return c;
}


#endif
