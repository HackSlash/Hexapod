package hexopod;

import com.jme3.asset.AssetManager;
import com.jme3.bullet.control.RigidBodyControl;
import com.jme3.material.Material;
import com.jme3.math.ColorRGBA;
import com.jme3.math.FastMath;
import com.jme3.math.Vector3f;
import com.jme3.scene.Geometry;
import com.jme3.scene.Node;
import com.jme3.scene.shape.Cylinder;
import com.jme3.scene.shape.Sphere;

public class Body extends Node {

    private Geometry geoHead; 
    private Geometry geoHead1; 
    private Geometry geoBody; 
    private RigidBodyControl body_phy;
    

    private AssetManager assetManager;

    public Body(AssetManager assetmanager) {
        
        assetManager = assetmanager; 
        initBody();
    }
  private void initBody(){
      Node node = new Node("body");
      Sphere  sphere = new Sphere(32, 32, 0.1f);
      geoHead = new Geometry("head", sphere);
      Material mat1 = new Material(assetManager, "Common/MatDefs/Misc/Unshaded.j3md");
      mat1.setColor("Color", ColorRGBA.Brown);
      geoHead.setMaterial(mat1);           
      
      Sphere  sphere1 = new Sphere(32, 32, 0.1f);
      geoHead1 = new Geometry("head", sphere1);
      Material mat2 = new Material(assetManager, "Common/MatDefs/Misc/Unshaded.j3md");
      mat2.setColor("Color", ColorRGBA.Brown);
      geoHead1.setMaterial(mat2);       
      geoHead1.setLocalTranslation(0, 0, 0.5f);
      geoHead.setLocalTranslation(0, 0, -0.5f);
      
        Cylinder cylinder = new Cylinder(30, 30, 0.1f, 1f, true);
        geoBody = new Geometry("body", cylinder);
        Material mat = new Material(assetManager, "Common/MatDefs/Misc/Unshaded.j3md");
        mat.setColor("Color", ColorRGBA.Brown);
        geoBody.setMaterial(mat);
        geoBody.setLocalTranslation(0, 0, 0);
        node.attachChild(geoHead);
        node.attachChild(geoHead1);
        node.attachChild(geoBody);
          // Make the floor physical with mass 0.0f! 
//        body_phy = new RigidBodyControl(0.0f);
//        floor.addControl( body_phy);
//        floor.addControl(new RigidBodyControl(0));
//        bulletAppState.getPhysicsSpace().add(floor_phy);
//        rootNode.attachChild(floor);
//        node
        this.attachChild(node);
    }
}