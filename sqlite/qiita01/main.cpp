#include "widget.h"
#include "common.h"

#include <tidy.h>
#include <tidybuffio.h>
#include <stdio.h>
#include <errno.h>

#include <pugixml.hpp>

std::string tidy(const std::string &input)
{
    std::string result = "";
    TidyBuffer output = {0};
    TidyBuffer errbuf = {0};
    int rc = -1;
    Bool ok;
    TidyDoc tdoc = tidyCreate();                     // Initialize "document"
    //printf( "Tidying:\t%s\n", input.c_str() );

    ok = tidyOptSetBool( tdoc, TidyXhtmlOut, yes );  // Convert to XHTML
    if ( ok )
      rc = tidySetErrorBuffer( tdoc, &errbuf );      // Capture diagnostics
    if ( rc >= 0 )
      rc = tidyParseString( tdoc, input.c_str() );           // Parse the input
    if ( rc >= 0 )
      rc = tidyCleanAndRepair( tdoc );               // Tidy it up!
    if ( rc >= 0 )
      rc = tidyRunDiagnostics( tdoc );               // Kvetch
    if ( rc > 1 )                                    // If error, force output.
      rc = ( tidyOptSetBool(tdoc, TidyForceOutput, yes) ? rc : -1 );
    if ( rc >= 0 )
      rc = tidySaveBuffer( tdoc, &output );          // Pretty Print

    if ( rc >= 0 )
    {
      if ( rc > 0 )
        printf( "\nDiagnostics:\n\n%s", errbuf.bp );
      //printf( "\nAnd here is the result:\n\n%s", output.bp );
      result = (const char *)output.bp;
    }
    else
      printf( "A severe error (%d) occurred.\n", rc );

    fflush(stdout);
    tidyBufFree( &output );
    tidyBufFree( &errbuf );
    tidyRelease( tdoc );
    return result;
}


std::string dump_node(const pugi::xml_node &node)
{
    std::ostringstream ss;
    node.print(ss);
    return ss.str();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Widget w;
    //w.show();
    qDebug() << "hello";
    QNetworkAccessManager nam;
    QUrl url("https://qiita.com/search?sort=created&q=created%3A2021-02-01&page=2");
    QNetworkRequest req(url);
    QNetworkReply *reply = nam.get(req);
    QEventLoop loop;
    while(!reply->isFinished())
    {
        loop.processEvents(QEventLoop::ExcludeUserInputEvents);
    }
    //qDebug() << QString::fromUtf8(reply->readAll());

    const std::string content = qstr_to_utf8(QString::fromUtf8(reply->readAll()));
    //const char* input = "<title>Foo</title><p>Foo!";
    const char *input = content.c_str();
    std::string tidy_result = tidy(input);
    //qDebug() << utf8_to_qstr(tidy_result);

    unicode_ostream uout(cout);
    uout << tidy_result << endl << flush;

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(tidy_result.c_str());
    //pugi::xml_parse_result result = doc.load_string(content.c_str());
    if (!result)
    {
        return -1;
    }

    pugi::xpath_node_set searchResults = doc.select_nodes("//div[@class='searchResult']");

    for (pugi::xpath_node searchResult: searchResults)
    {
        qDebug() << "found!";
        //auto prev = searchResult.node().previous_sibling();
        //uout << "★prev=" << dump_node(prev) << endl;
        uout << "★self=" << dump_node(searchResult.node()) << endl;
        auto title = searchResult.node().select_node("*/*[@class='searchResult_itemTitle']/a[1]/text()");
        uout << "★title=" << dump_node(title.node()) << endl;
        uout << "★title=" << title.node().value() << endl;
        auto sub = searchResult.node().select_node("*/*[@class='searchResult_sub']");
        uout << "★sub=" << dump_node(sub.node()) << endl;
#if 0x0
        pugi::xml_node tool = node.node();
        std::cout << "Tool " << tool.attribute("Filename").value() <<
            " has timeout " << tool.attribute("Timeout").as_int() << "\n";
#endif
    }

    return a.exec();
}
