import java.io.IOException;

import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

class Item {
    public String created_at;
    public String title;
}

public class Main {

    public static void main(String[] args) throws IOException {
        System.out.println("hello");
        Document document = Jsoup.connect("https://qiita.com/search")
            .userAgent("Mozilla/5.0 (Windows NT 6.2; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/32.0.1667.0 Safari/537.36")
            .header("Accept-Language", "ja-JP")
            .data("q", "created:2019-02-09")
            .data("sort", "created")
            .get();
        System.out.println(document.html());
        Elements elements = document.select(".searchResult");
        for (Element element : elements) {
            System.out.println("=====");
            System.out.println(element.outerHtml());
            System.out.println("=====");
        }
    }

}