//! Qore namespace
namespace Qore {
//! Markdown namespace
namespace Markdown {
/** @defgroup markdown_functions Markdown Functions
*/
///@{

//! Convert markdown string to HTML
/**@par Code Flags:
    @ref RET_VALUE_ONLY

*/
string markdown_convert(string input);

//! get sundown's markdown version
/**@par Code Flags:
    @ref RET_VALUE_ONLY

*/
string markdown_version();

///@}
}
}
