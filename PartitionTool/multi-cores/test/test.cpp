/*
 * Author: Shao Yingxia
 * Create Date: 2012年12月10日 星期一 14时17分26秒
 */

#include <core/graphkinfe.h>

using namespace std;

int main(int argc, char** args) {
    GraphKinfe gkinfe(argc, args);
    Logger(LOG_DEBUG, "Begin start....\n");
    gkinfe.Start();
    return 0;
}

