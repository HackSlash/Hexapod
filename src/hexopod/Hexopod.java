package hexopod;

import com.jme3.asset.AssetManager;
import com.jme3.bullet.BulletAppState;
import com.jme3.bullet.collision.shapes.MeshCollisionShape;
import com.jme3.bullet.control.RigidBodyControl;
import com.jme3.math.Vector3f;
import com.jme3.scene.Node;

public class Hexopod extends Node {
    
    Vector3f spawnLocation;
    AssetManager assetManager;
    BulletAppState BAS;
    RigidBodyControl rigBC;
    
    
    Leg rightFront;
    Leg rightMid;
    Leg rightBack;
    Leg leftFront;
    Leg leftMid;
    Leg leftBack;
    
    Body body;

    public Hexopod(Vector3f spawnLocation, AssetManager assetmanager) {
        this.spawnLocation = spawnLocation;
        this.assetManager = assetmanager;
        
       BAS = new BulletAppState();
       //stateManager.attach(BAS);
        
        init();
        setup();
        attach();
    }

    
    private void init(){
        
        body = new Body(assetManager);
        rightFront = new Leg(1,assetManager);
        rightMid = new Leg(2,assetManager);
        rightBack = new Leg(3,assetManager);
        leftFront = new Leg(4,assetManager);
        leftMid = new Leg(5,assetManager);
        leftBack = new Leg(6,assetManager);    
    }
    
    private void setup() {
        
        // body
        body.setLocalTranslation(0, 0.4f, 0);       
        
        //right side
        
        rightFront.setLocalTranslation(0,0.4f,0.7f);
        rightMid.setLocalTranslation(0,0.4f,0);
        rightBack.setLocalTranslation(0,0.4f,-0.7f);
        
        //left side
        leftFront.setLocalTranslation(0,0.4f,0.7f);
        leftMid.setLocalTranslation(0,0.4f,0);
        leftBack.setLocalTranslation(0,0.4f,-0.7f);
        
        
//    rigBC = new RigidBodyControl(0.01f);
//    
//    body.addControl(rigBC);
//    rightFront.addControl(rigBC);
//    rightMid.addControl(rigBC);
//    rightBack.addControl(rigBC);
//    leftFront.addControl(rigBC);
//    leftMid.addControl(rigBC);
//    leftBack.addControl(rigBC);
    
//    BAS.getPhysicsSpace().add(rigBC);
//        
//        body.addControl(new RigidBodyControl(0.1f));
//        rightFront.addControl(new RigidBodyControl(0.1f));
//        rightMid.addControl(new RigidBodyControl(0.1f));
//        rightBack.addControl(new RigidBodyControl(0.1f));
//        leftFront.addControl(new RigidBodyControl(0.1f));
//        leftMid.addControl(new RigidBodyControl(0.1f));
//        leftBack.addControl(new RigidBodyControl(0.1f));
        
       // BAS.getPhysicsSpace().add(rigBC);
    
    }
    
    private void attach(){

        
        //body
        this.attachChild(body);
        
        //left side
        this.attachChild(rightFront);
        this.attachChild(rightMid);
        this.attachChild(rightBack);
        
        //right side
        this.attachChild(leftFront);
        this.attachChild(leftMid);
        this.attachChild(leftBack);  
        
    }
    
    
        
        
        
        

    
    
    
    
    
}
