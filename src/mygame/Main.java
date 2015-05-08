package mygame;

import com.jme3.app.SimpleApplication;
import com.jme3.bullet.BulletAppState;
import com.jme3.bullet.PhysicsSpace;
import com.jme3.bullet.collision.shapes.BoxCollisionShape;
import com.jme3.bullet.collision.shapes.CapsuleCollisionShape;
import com.jme3.bullet.collision.shapes.CollisionShape;
import com.jme3.bullet.collision.shapes.MeshCollisionShape;
//import com.jme3.bullet.collision.shapes.MeshCollisionShape;
import com.jme3.bullet.control.RigidBodyControl;
import com.jme3.bullet.control.CharacterControl;
import com.jme3.bullet.util.CollisionShapeFactory;
import com.jme3.material.Material;
import com.jme3.math.ColorRGBA;
import com.jme3.math.Vector3f;
import com.jme3.renderer.RenderManager;
import com.jme3.scene.Geometry;
import com.jme3.scene.Node;
import com.jme3.scene.Spatial;
import com.jme3.scene.shape.Box;
import com.jme3.scene.shape.Sphere;
import hexopod.Hexopod;

/**
 * @author Azad & HackSlash
 */
public class Main extends SimpleApplication {

    public static void main(String[] args) {
        Main app = new Main();
        app.start();
    }
    private BulletAppState BAS;
    private RigidBodyControl rigBC;
    private RigidBodyControl floor_phy;
    private Geometry geoBody;  //middelste lichaamsdeel
    Hexopod hexopod;
    
    Spatial terrain;
    RigidBodyControl terrainRBC;
    
    CharacterControl playerHex;
    
    
    
   // private Node hipNode;
    @Override
    public void simpleInitApp() {
       hexopod = new Hexopod(Vector3f.ZERO, assetManager);
       hexopod.setLocalTranslation(0, 10, 0);
      // hexopod.addControl(new RigidBodyControl(.001f));
       BAS = new BulletAppState();
       stateManager.attach(BAS);
       
      //    setupFloor();
        
        
      //  flyCam.setEnabled(true);
        flyCam.setMoveSpeed(4f);
        cam.setLocation(new Vector3f(12, 7.02f, 14));
        cam.lookAt(new Vector3f(0, 0, 0), Vector3f.ZERO);
    
    //////
     Material material = new Material(assetManager, "Common/MatDefs/Misc/Unshaded.j3md");
        material.setTexture("ColorMap", assetManager.loadTexture("Textures/dirt.jpg"));

        //immovable sphere with mesh collision shape
        Sphere sphere = new Sphere(8, 9, 0.6F);
        Geometry sphereGeometry = new Geometry("Sphere", sphere);
        sphereGeometry.setMaterial(material);
        sphereGeometry.setLocalTranslation(0.8f, 20, 0);
       // sphereGeometry.addControl(new RigidBodyControl(new MeshCollisionShape(sphere), 0));
        
    rigBC = new RigidBodyControl(0.1f);
    sphereGeometry.addControl(rigBC);
    BAS.getPhysicsSpace().add(rigBC);
    
    rigBC = new RigidBodyControl(0.01f);
    hexopod.addControl(rigBC);
    BAS.getPhysicsSpace().add(rigBC);
    
     rootNode.attachChild(hexopod);
     rootNode.attachChild(sphereGeometry);
    
          
//       CollisionShape sceneShape =
//      CollisionShapeFactory.createMeshShape((Node) sceneModel);
//    landscape = new RigidBodyControl(sceneShape, 0);
//    sceneModel.addControl(landscape);
//    rootNode.attachChild(sceneModel);
     
       //add terrain to the space 
       terrain = assetManager.loadModel("Scenes/Scene.j3o"); //importing the terrain we made  
       CollisionShape cs = CollisionShapeFactory.createMeshShape(terrain); //creating collisionshape of oure terrain
       terrainRBC = new RigidBodyControl(cs, 0); // oure terrain has a 0 mass to stay in his place.
       terrain.addControl(terrainRBC);
       
        CapsuleCollisionShape playerC = new CapsuleCollisionShape(0, 0.2f, 0);
        playerHex = new CharacterControl(playerC, 0.3f);
        playerHex.setPhysicsLocation(new Vector3f(0, 0.5f, 0));
        
      // BAS.getPhysicsSpace().add(terrain);
        BAS.getPhysicsSpace().add(terrainRBC);
        BAS.getPhysicsSpace().add(playerHex);
        
       rootNode.attachChild(terrain);
    
    }
      public void setupFloor() {
              // create floor
    Box FloorBox = new Box(10f, 0.1f, 10f);// {}{}{lengte floor}
    Material floor_mat = new Material(assetManager, "Common/MatDefs/Misc/Unshaded.j3md");   
    floor_mat.setTexture("ColorMap", assetManager.loadTexture("Textures/dirt.jpg"));
    Geometry floor_geo = new Geometry("Floor", FloorBox);
    floor_geo.setMaterial(floor_mat);
    floor_geo.setLocalTranslation(0, -1.1f, 0);
    this.rootNode.attachChild(floor_geo);
    /* Make the floor physical with mass 0.0f! */
    floor_phy = new RigidBodyControl(0.0f);
    floor_geo.addControl(floor_phy);
   // BAS.getPhysicsSpace().add(floor_phy);
    
    CollisionShape createMeshShape = CollisionShapeFactory.createMeshShape(floor_geo);
    rootNode.attachChild(floor_geo);
    getPhysicsSpace().add(floor_geo);  

    }
    
private PhysicsSpace getPhysicsSpace(){
        return BAS.getPhysicsSpace();
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