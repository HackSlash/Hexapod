package mygame;

import com.jme3.app.SimpleApplication;
import com.jme3.renderer.RenderManager;
import hexopod.Leg;

/**
 * @author Azad & HackSlash
 */
public class Main extends SimpleApplication {

    public static void main(String[] args) {
        Main app = new Main();
        app.start();
    }

    @Override
    public void simpleInitApp() {
        Leg been = new Leg(1, assetManager);
        rootNode.attachChild(been);
    }

    @Override
    public void simpleUpdate(float tpf) {
        //TODO: add update code
    }

    @Override
    public void simpleRender(RenderManager rm) {
        //TODO: add render code
    }
}
