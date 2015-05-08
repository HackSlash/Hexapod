package hexopod;

import com.jme3.app.state.AppStateManager;
import com.jme3.asset.AssetManager;
import com.jme3.bullet.BulletAppState;
import com.jme3.bullet.collision.shapes.CapsuleCollisionShape;
import com.jme3.bullet.collision.shapes.CollisionShape;
import com.jme3.bullet.collision.shapes.MeshCollisionShape;
import com.jme3.bullet.control.CharacterControl;
import com.jme3.bullet.control.RigidBodyControl;
import com.jme3.bullet.util.CollisionShapeFactory;
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
    private Geometry geoBack; 
    private Geometry geoBody; 
    private RigidBodyControl body_phy;
    private CharacterControl player;
    private BulletAppState BAS;
    protected AppStateManager stateManager;
    

    private AssetManager assetManager;

    public Body(AssetManager assetmanager) {
        
        assetManager = assetmanager; 
        initBody();
    }
  private void initBody(){
      
      Node node = new Node("body");
      
      Sphere  sphereHead = new Sphere(32, 32, 0.1f);
      geoHead = new Geometry("head", sphereHead);
      Material mat1 = new Material(assetManager, "Common/MatDefs/Misc/Unshaded.j3md");
      mat1.setColor("Color", ColorRGBA.Red);
      geoHead.setMaterial(mat1);   
      geoHead.setLocalTranslation(0, 0, -0.8f);

      Sphere  sphereBack = new Sphere(32, 32, 0.1f);
      geoBack = new Geometry("back", sphereBack);
      Material mat2 = new Material(assetManager, "Common/MatDefs/Misc/Unshaded.j3md");
      mat2.setColor("Color", ColorRGBA.Brown);
      geoBack.setMaterial(mat2);       
      geoBack.setLocalTranslation(0, 0, 0.8f);
     
      
        Cylinder cylinder = new Cylinder(30, 30, 0.1f, 1.6f, true);
        geoBody = new Geometry("body", cylinder);
        Material mat = new Material(assetManager, "Common/MatDefs/Misc/Unshaded.j3md");
        mat.setColor("Color", ColorRGBA.Brown);
        geoBody.setMaterial(mat);
        geoBody.setLocalTranslation(0, 0, 0);
        
        node.attachChild(geoHead);
        node.attachChild(geoBack);
        node.attachChild(geoBody);       
            
        this.attachChild(node);
    }
}