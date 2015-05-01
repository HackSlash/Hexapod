
#include "JNIDemoJava.h"

JNIEXPORT void JNICALL Java_jnidemojava_Main_nativePrint
        (JNIEnv *env, jobject obj)
{

    printf("\nHello World from C\n");

}

