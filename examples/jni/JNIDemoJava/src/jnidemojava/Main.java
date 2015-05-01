/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package jnidemojava;

/**
 *
 * @author smorgan
 */
public class Main {
static {
        System.load("/home/testuser/ForJNITutorial/JNIDemoCdl/dist/libJNIDemoCdl.so");
       }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        new Main().nativePrint();
    }

    private native void nativePrint();
}

   
    