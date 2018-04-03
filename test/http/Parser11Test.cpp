#include <gtest/gtest.h>
#include <panda/http/Parser11.h>
#include <sstream>
#include <string>

namespace panda {
namespace http {

const std::string uri =
    "/wp-content/uploads/2010/03/hello-kitty-darth-vader-pink.jpg";

const std::string userAgent =
    "Mozilla/5.0 (Macintosh; U; Intel Mac OS X 10.6; ja-JP-mac; "
    "rv:1.9.2.3) Gecko/20100401 Firefox/3.6.3 "
    "Pathtraq/0.9";

const std::string getReq0 =
    "GET /wp-content/uploads/2010/03/hello-kitty-darth-vader-pink.jpg "
    "HTTP/1.1\r\n"
    "Host: www.kittyhell.com\r\n"
    "User-Agent: Mozilla/5.0 (Macintosh; U; Intel Mac OS X 10.6; ja-JP-mac; "
    "rv:1.9.2.3) Gecko/20100401 Firefox/3.6.3 "
    "Pathtraq/0.9\r\n"
    "    Accept: "
    "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
    "Accept-Language: ja,en-us;q=0.7,en;q=0.3\r\n"
    "Accept-Encoding: gzip,deflate\r\n"
    "Accept-Charset: Shift_JIS,utf-8;q=0.7,*;q=0.7\r\n"
    "Keep-Alive: 115\r\n"
    "Connection: keep-alive\r\n"
    "Cookie: wp_ozh_wsa_visits=2; wp_ozh_wsa_visit_lasttime=xxxxxxxxxx; "
    "__utma=xxxxxxxxx.xxxxxxxxxx.xxxxxxxxxx.xxxxxxxxxx.xxxxxxxxxx.x; "
    "__utmz=xxxxxxxxx.xxxxxxxxxx.x.x.utmccn=(referral)|utmcsr=reader.livedoor."
    "com|utmcct=/reader/|utmcmd=referral\r\n"
    "\r\n";

const std::string getReq =
    "GET /wp-content/uploads/2010/03/hello-kitty-darth-vader-pink.jpg "
    "HTTP/1.1\r\n"
    "Host: www.kittyhell.com\r\n"
    "User-Agent: Mozilla/5.0 (Macintosh; U; Intel Mac OS X 10.6; ja-JP-mac; "
    "rv:1.9.2.3) Gecko/20100401 Firefox/3.6.3 "
    "Pathtraq/0.9\r\n"
    "Accept: "
    "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
    "Accept-Language: ja,en-us;q=0.7,en;q=0.3\r\n"
    "Accept-Encoding: gzip,deflate\r\n"
    "Accept-Charset: Shift_JIS,utf-8;q=0.7,*;q=0.7\r\n"
    "Keep-Alive: 115\r\n"
    "Connection: keep-alive\r\n"
    "Cookie: wp_ozh_wsa_visits=2; wp_ozh_wsa_visit_lasttime=xxxxxxxxxx; "
    "__utma=xxxxxxxxx.xxxxxxxxxx.xxxxxxxxxx.xxxxxxxxxx.xxxxxxxxxx.x; "
    "__utmz=xxxxxxxxx.xxxxxxxxxx.x.x.utmccn=(referral)|utmcsr=reader.livedoor."
    "com|utmcct=/reader/|utmcmd=referral\r\n"
    "\r\n";

const std::string postReqPart0 =
    "POST /wp-content/uploads/2010/03/hello-kitty-darth-vader-pink.jpg "
    "HTTP/1.1\r\n"
    "Host: www.kittyhell.com\r\n"
    "User-Agent: Mozilla/5.0 (Macintosh; U; Intel Mac OS X 10.6; ja-JP-mac; "
    "rv:1.9.2.3) Gecko/20100401 Firefox/3.6.3 "
    "Pathtraq/0.9\r\n"
    "Accept: "
    "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
    "Accept-Language: ja,en-us;q=0.7,en;q=0.3\r\n"
    "Accept-Encoding: gzip,deflate\r\n"
    "Accept-Charset: Shift_JIS,utf-8;q=0.7,*;q=0.7\r\n"
    "Keep-Alive: 115\r\n"
    "Connection: keep-alive\r\n"
    "Content-Type: application/json\r\n"
    "Content-Length: ";

const std::string postReqPart1 =
    "\r\n"
    "Cookie: wp_ozh_wsa_visits=2; wp_ozh_wsa_visit_lasttime=xxxxxxxxxx; "
    "__utma=xxxxxxxxx.xxxxxxxxxx.xxxxxxxxxx.xxxxxxxxxx.xxxxxxxxxx.x; "
    "__utmz=xxxxxxxxx.xxxxxxxxxx.x.x.utmccn=(referral)|utmcsr=reader.livedoor."
    "com|utmcct=/reader/|utmcmd=referral\r\n"
    "\r\n";

const std::string jsonStr =
    "{\"web-app\": {"
    "\"servlet\": ["
    "{"
    "\"servlet-name\": \"cofaxCDS\","
    "\"servlet-class\": \"org.cofax.cds.CDSServlet\","
    "\"init-param\": {"
    "\"configGlossary:installationAt\": \"Philadelphia, PA\","
    "\"configGlossary:adminEmail\": \"ksm@pobox.com\","
    "\"configGlossary:poweredBy\": \"Cofax\","
    "\"configGlossary:poweredByIcon\": \"/images/cofax.gif\","
    "\"configGlossary:staticPath\": \"/content/static\","
    "\"templateProcessorClass\": \"org.cofax.WysiwygTemplate\","
    "\"templateLoaderClass\": \"org.cofax.FilesTemplateLoader\","
    "\"templatePath\": \"templates\","
    "\"templateOverridePath\": \"\","
    "\"defaultListTemplate\": \"listTemplate.htm\","
    "\"defaultFileTemplate\": \"articleTemplate.htm\","
    "\"useJSP\": false,"
    "\"jspListTemplate\": \"listTemplate.jsp\","
    "\"jspFileTemplate\": \"articleTemplate.jsp\","
    "\"cachePackageTagsTrack\": 200,"
    "\"cachePackageTagsStore\": 200,"
    "\"cachePackageTagsRefresh\": 60,"
    "\"cacheTemplatesTrack\": 100,"
    "\"cacheTemplatesStore\": 50,"
    "\"cacheTemplatesRefresh\": 15,"
    "\"cachePagesTrack\": 200,"
    "\"cachePagesStore\": 100,"
    "\"cachePagesRefresh\": 10,"
    "\"cachePagesDirtyRead\": 10,"
    "\"searchEngineListTemplate\": \"forSearchEnginesList.htm\","
    "\"searchEngineFileTemplate\": \"forSearchEngines.htm\","
    "\"searchEngineRobotsDb\": \"WEB-INF/robots.db\","
    "\"useDataStore\": true,"
    "\"dataStoreClass\": \"org.cofax.SqlDataStore\","
    "\"redirectionClass\": \"org.cofax.SqlRedirection\","
    "\"dataStoreName\": \"cofax\","
    "\"dataStoreDriver\": \"com.microsoft.jdbc.sqlserver.SQLServerDriver\","
    "\"dataStoreUrl\": "
    "\"jdbc:microsoft:sqlserver://LOCALHOST:1433;DatabaseName=goon\","
    "\"dataStoreUser\": \"sa\","
    "\"dataStorePassword\": \"dataStoreTestQuery\","
    "\"dataStoreTestQuery\": \"SET NOCOUNT ON;select test='test';\","
    "\"dataStoreLogFile\": \"/usr/local/tomcat/logs/datastore.log\","
    "\"dataStoreInitConns\": 10,"
    "\"dataStoreMaxConns\": 100,"
    "\"dataStoreConnUsageLimit\": 100,"
    "\"dataStoreLogLevel\": \"debug\","
    "\"maxUrlLength\": 500}},"
    "{"
    "\"servlet-name\": \"cofaxEmail\","
    "\"servlet-class\": \"org.cofax.cds.EmailServlet\","
    "\"init-param\": {"
    "\"mailHost\": \"mail1\","
    "\"mailHostOverride\": \"mail2\"}},"
    "{"
    "\"servlet-name\": \"cofaxAdmin\","
    "\"servlet-class\": \"org.cofax.cds.AdminServlet\"},"

    "{"
    "\"servlet-name\": \"fileServlet\","
    "\"servlet-class\": \"org.cofax.cds.FileServlet\"},"
    "{"
    "\"servlet-name\": \"cofaxTools\","
    "\"servlet-class\": \"org.cofax.cms.CofaxToolsServlet\","
    "\"init-param\": {"
    "\"templatePath\": \"toolstemplates/\","
    "\"log\": 1,"
    "\"logLocation\": \"/usr/local/tomcat/logs/CofaxTools.log\","
    "\"logMaxSize\": \"\","
    "\"dataLog\": 1,"
    "\"dataLogLocation\": \"/usr/local/tomcat/logs/dataLog.log\","
    "\"dataLogMaxSize\": \"\","
    "\"removePageCache\": \"/content/admin/remove?cache=pages&id=\","
    "\"removeTemplateCache\": \"/content/admin/remove?cache=templates&id=\","
    "\"fileTransferFolder\": "
    "\"/usr/local/tomcat/webapps/content/fileTransferFolder\","
    "\"lookInContext\": 1,"
    "\"adminGroupID\": 4,"
    "\"betaServer\": true}}],"
    "\"servlet-mapping\": {"
    "\"cofaxCDS\": \"/\","
    "\"cofaxEmail\": \"/cofaxutil/aemail/*\","
    "\"cofaxAdmin\": \"/admin/*\","
    "\"fileServlet\": \"/static/*\","
    "\"cofaxTools\": \"/tools/*\"},"

    "\"taglib\": {"
    "\"taglib-uri\": \"cofax.tld\","
    "\"taglib-location\": \"/WEB-INF/tlds/cofax.tld\"}}}";

const std::string simplePostReq =
    "POST /echo HTTP/1.1\r\n"
    "Host: localhost:8080\r\n"
    "User-Agent: curl/7.54.0\r\n"
    "Accept: */*\r\n"
    "Content-Type: application/json\r\n"
    "Content-Length: 35\r\n\r\n"
    "{\"username\":\"xyz\",\"password\":\"xyz\"}";

TEST(Parser11Test, ParseGETRequest0) {
  Parser11 parser;

  ASSERT_TRUE(parser.append(getReq0.c_str(), getReq0.length()));
  auto result = parser.run();
  ASSERT_EQ(result.status, Parser11::ResultStatus::Error);
}

TEST(Parser11Test, ParseGETRequest1) {
  Parser11 parser;

  ASSERT_TRUE(parser.append(getReq.c_str(), getReq.length() - 1));
  auto result = parser.run();
  ASSERT_NE(result.status, Parser11::ResultStatus::Finished);
  ASSERT_EQ(result.status, Parser11::ResultStatus::PartialHeaders);
  ASSERT_TRUE(!parser.empty());

  ASSERT_TRUE(parser.append("\n", 1));
  result = parser.run();
  ASSERT_EQ(result.status, Parser11::ResultStatus::Finished);
  ASSERT_TRUE(parser.empty());

  ASSERT_FALSE(result.resp);
  auto req = result.req;
  ASSERT_TRUE(req);
  ASSERT_TRUE(req->method() == http::Method::GET);
  ASSERT_TRUE(req->path() == uri);
  ASSERT_TRUE(req->header("User-Agent").get() == userAgent);
}

TEST(Parser11Test, ParseGETRequest2) {
  Parser11 parser;

  size_t repeatCount = 13;
  std::ostringstream oss;
  for (size_t i = 0; i < repeatCount; i++) {
    oss << getReq;
  }
  auto s = oss.str();
  ASSERT_TRUE(parser.append(s.c_str(), s.length()));

  size_t count = 0;
  while (!parser.empty()) {
    auto result = parser.run();
    ++count;
    ASSERT_EQ(result.status, Parser11::ResultStatus::Finished);
    auto req = result.req;
    ASSERT_TRUE(req);
    ASSERT_EQ(req->header("User-Agent").get(), userAgent);
  }
  ASSERT_EQ(repeatCount, count);
  ASSERT_TRUE(parser.empty());
}

TEST(Parser11Test, ParseGETRequest3) {
  Parser11 parser;

  size_t repeatCount = 17;
  std::ostringstream oss;
  for (size_t i = 0; i < repeatCount; i++) {
    oss << getReq;
  }
  auto s = oss.str();

  const std::string trailer = "referral\r\n\r\n";
  ASSERT_TRUE(parser.append(s.c_str(), s.length() - trailer.length()));

  size_t count = 0;
  while (!parser.empty()) {
    auto result = parser.run();
    ++count;
    if (count == repeatCount) {
      ASSERT_EQ(result.status, Parser11::ResultStatus::PartialHeaders);
      ASSERT_TRUE(!parser.empty());
      ASSERT_TRUE(parser.append(trailer.c_str(), trailer.length()));
      result = parser.run();
      ASSERT_EQ(result.status, Parser11::ResultStatus::Finished);
      auto req = result.req;
      ASSERT_TRUE(req);
      ASSERT_EQ(req->header("User-Agent").get(), userAgent);
      ASSERT_TRUE(parser.empty());
    } else {
      ASSERT_EQ(result.status, Parser11::ResultStatus::Finished);
      auto req = result.req;
      ASSERT_TRUE(req);
      ASSERT_EQ(req->method(), http::Method::GET);
      ASSERT_EQ(req->header("User-Agent").get(), userAgent);
    }
  }
  ASSERT_EQ(repeatCount, count);
}

TEST(Parser11Test, PostRequest0) {
  Parser11 parser;

  parser.append(simplePostReq.c_str(), simplePostReq.size());
  while (!parser.empty()) {
    auto result = parser.run();
    ASSERT_EQ(result.status, Parser11::ResultStatus::Finished);
    auto req = result.req;
    ASSERT_TRUE(req);
    ASSERT_EQ(req->method(), http::Method::POST);
  }
}

TEST(Parser11Test, PostRequest1) {
  Parser11 parser;

  std::ostringstream oss;
  oss << postReqPart0 << jsonStr.size() << postReqPart1 << jsonStr;
  auto s = oss.str();

  size_t repeatCount = 3;
  std::ostringstream oss2;
  for (size_t i = 0; i < repeatCount; i++) {
    oss2 << s;
  }
  s = oss2.str();

  ASSERT_TRUE(parser.append(s.c_str(), s.size()));

  size_t count = 0;
  while (!parser.empty()) {
    auto result = parser.run();
    ++count;
    ASSERT_EQ(result.status, Parser11::ResultStatus::Finished);

    ASSERT_FALSE(result.resp);
    auto req = result.req;
    ASSERT_TRUE(req);
    ASSERT_EQ(req->method(), http::Method::POST);
    ASSERT_EQ(req->path(), uri);
    ASSERT_EQ(req->header("User-Agent").get(), userAgent);
    ASSERT_TRUE(req->parseBody());
  }
  ASSERT_EQ(count, repeatCount);
}

}  // namespace http
}  // namespace panda