package mygame;

import com.jme3.app.SimpleApplication;
import com.jme3.bullet.BulletAppState;
import com.jme3.bullet.control.RigidBodyControl;
import com.jme3.material.Material;
import com.jme3.math.ColorRGBA;
import com.jme3.math.Vector2f;
import com.jme3.math.Vector3f;
import com.jme3.renderer.Camera;
import com.jme3.renderer.RenderManager;
import com.jme3.scene.Geometry;
import com.jme3.scene.Node;
import com.jme3.scene.shape.Box;
import com.jme3.texture.Texture;
import hexopod.Leg;
import hexopod.Body;

/**
 * @author Azad & HackSlash
 */
public class Main extends SimpleApplication {

    public static void main(String[] args) {
        Main app = new Main();
        app.start();
    }
    private BulletAppState bulletAppState;
    private RigidBodyControl floor_phy;
    private Geometry geoBody;  //middelste lichaamsdeel
    
   // private Node hipNode;
    @Override
    public void simpleInitApp() {
    
        Leg hip = new Leg(1, assetManager);
        Leg thigh = new Leg(2, assetManager);
        Leg knee = new Leg(3, assetManager);
        Leg leg = new Leg(4, assetManager);
        Leg ankle = new Leg(5, assetManager);
        Leg base = new Leg(6, assetManager);
        Body body = new Body(assetManager);
        
        
        thigh.setLocalTranslation(0f, 0, 0.1f);
        knee.setLocalTranslation(0f, 0, 0.25f);
        leg.setLocalTranslation(0f, 0, 0.25f);
        ankle.setLocalTranslation(0, 0, 0.20f);
        base.setLocalTranslation(0, 0, 0.3f);
        
        ankle.attachChild(base);
        leg.attachChild(ankle);
        knee.attachChild(leg);
        
        knee.rotate(-1, 0, 0); 
        ankle.rotate(2.2f, 0, 0);
        
        hip.attachChild(thigh);
        hip.attachChild(knee);
        hip.rotate(0, -2, 0);
        body.setLocalTranslation(0, 0.4f, 0);
        hip.setLocalTranslation(-0.1f, 0, 0);
        body.attachChild(hip);
        
       
        rootNode.attachChild(body);
        
        //flyCam.setEnabled(true);
        cam.setLocation(new Vector3f(0f, 2f, -2f));
        cam.lookAt(new Vector3f(0, 0, 0), Vector3f.ZERO);
       
        // bullet
        bulletAppState = new BulletAppState();
        stateManager.attach(bulletAppState);

        
        // create floor
        Box FloorBox = new Box(10f, 0.1f, 10f);// {}{}{lengte floor}
        Geometry floor = new Geometry("the Floor", FloorBox);
        floor.setLocalTranslation(0, -0.1f, 0);
        Material floor_mat = new Material(assetManager, "Common/MatDefs/Misc/Unshaded.j3md");
        floor_mat.setColor("Color", ColorRGBA.White);
        floor.setMaterial(floor_mat);
        
        
     // Make the floor physical with mass 0.0f! 
        floor_phy = new RigidBodyControl(0.0f);
        floor.addControl(floor_phy);
        floor.addControl(new RigidBodyControl(0));
        bulletAppState.getPhysicsSpace().add(floor_phy);
        rootNode.attachChild(floor);
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