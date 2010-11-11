#import "common.h"
#import <boost/shared_ptr.hpp>
#import <srchilite/formatter.h>
#import <srchilite/formatterfactory.h>

@class KSyntaxHighlighter;

/**
 * Constitutes the text attributes for a specific language element.
 *
 * Part of the source-highlight API. srchilite::Formatter is an interface which
 * defines a single method |format(text, params)|.
 *
 * KStyleElements are owned by KStyle objects:
 *
 *    KStyle
 *      dict { element-id => KStyleElement , .. }
 *
 */
class KStyleElement : public srchilite::Formatter {
 protected:
  /// the language element represented by this formatter
  std::string elem_;

  /// reference to related KSyntaxHighlighter
  KSyntaxHighlighter *syntaxHighlighter_;
  
  NSMutableDictionary *textAttributes_;

 public:
  static NSFont *baseFont();
  static NSString *ClassAttributeName;
  
  static void clearAttributes(NSMutableAttributedString *astr,
                              NSRange range,
                              bool removeSpecials=false);
  
  KStyleElement(const std::string &elem = "normal");
  virtual ~KStyleElement();

  /// the language element represented by this formatter
  const std::string &getElem() const { return elem_; }
  void setElem(const std::string &e);

  inline void setSyntaxHighlighter(KSyntaxHighlighter *syntaxHighlighter) {
    objc_exch(&syntaxHighlighter_, syntaxHighlighter);
  }
  
  /// Set the style of this formatter
  void setStyle(srchilite::StyleConstantsPtr style);
  inline NSDictionary *textAttributes() { return textAttributes_; }

  void setForegroundColor(const std::string &color);
  void setForegroundColor(NSColor *color);
  NSColor *foregroundColor();

  void setBackgroundColor(const std::string &color);
  void setBackgroundColor(NSColor *color);
  NSColor *backgroundColor();
  
  /**
   * Applies attributes to |astr| in |range|. If |replace| is true, any existing
   * atributes will be removed (replaced with my attributes).
   */
  void applyAttributes(NSMutableAttributedString *astr,
                       NSRange range,
                       bool replace=false);

  /**
   * Formats the passed string.
   *
   * @param the string to format
   * @param params possible additional parameters for the formatter
   */
  void format(const std::string &text,
              const srchilite::FormatterParams *params = 0);
};

/// shared pointer for KStyleElement
typedef boost::shared_ptr<KStyleElement> KStyleElementPtr;