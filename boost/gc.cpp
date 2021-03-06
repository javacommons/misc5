// https://qiita.com/Gajumaru/items/195adf964d3932e6dc57
#include <gc/gc_cpp.h>
#include <gc/javaxfc.h>

#include "strconv.h"

int ccnt;
int dcnt;

class Hoge : public gc_cleanup
{
public:
    Hoge() {
        ccnt++;
    }
    ~Hoge() {
        dcnt++;
    }
};

int main()
{
    unicode_ostream uout(std::cout);
    for (int i = 0; i < 100000; i++) {
        Hoge *h = new Hoge();
    }
    GC_finalize_all();
    uout<<"コンストラクタが呼ばれた数："<<ccnt<<std::endl;
    uout<<"デストラクタが呼ばれた数："<<dcnt<<std::endl;
    return 0;
}
