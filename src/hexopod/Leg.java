package hexopod;

import com.jme3.asset.AssetManager;
import com.jme3.material.Material;
import com.jme3.math.ColorRGBA;
import com.jme3.math.FastMath;
import com.jme3.math.Vector3f;
import com.jme3.scene.Geometry;
import com.jme3.scene.Node;
import com.jme3.scene.shape.Box;
import com.jme3.scene.shape.Cylinder;

public class Leg extends Node {

    private Geometry hip;   //servo         :heup
    private Geometry thigh; //beenonderdeel :Bovenbeen
    private Geometry knee;  //servo         :Knie
    private Geometry leg;   //beenonderdeel :Onderbeen
    private Geometry ankle; //servo         :enkel
    private Geometry base;  //beenonderdeel :voet
    
    private Node hipNode;
    private Node kneeNode;
    private Node ankleNode;
    private Node thighNode;
    private Node legNode;
    private Node baseNode;

    
    
    
    private int id;
    private AssetManager assetManager;

    public Leg(int id, AssetManager assetmanager) {
        
        assetManager = assetmanager;
        
        switch (id) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
                default:
                    
        }
      
        

    }
    public Leg(AssetManager assetmanager){
        assetManager = assetmanager;
                initNodes();
                initHip();
                initThigh();
                initKnee();
                initLeg();
                initAnkle();
                initBase();
                setupParts();                                    
    }
    /*
     * NOTES
     * *******
     * 
     * Hip under thigh.
     * resize thigh.
     * Added subNodes
     * 
     */
    
    private void initNodes() {
        
        ankleNode = new Node();
        baseNode = new Node();
    }
    
    private void setupParts() {
        
        hipNode.setLocalTranslation(-0.1f, 0, 0);
       kneeNode.rotate(0,0, -1f); 
        hipNode.rotate(0, 0, 0f);
        this.attachChild(hipNode);
    }

    private void initHip() {
        Cylinder smallCylinder = new Cylinder(20, 20, 0.07f, 0.1f, true);
        hip = new Geometry("Hip", smallCylinder);
        Material mat = new Material(assetManager, "Common/MatDefs/Misc/Unshaded.j3md");
        mat.setColor("Color", ColorRGBA.Red);
        hip.setMaterial(mat);
        hipNode = new Node();
        hipNode.attachChild(hip);
        hipNode.setLocalTranslation(-0.1f, 0, 0);
        hipNode.rotate(FastMath.HALF_PI, 0f, 0);
        hipNode.rotate(0, 0, -1.6f);
    }
    
    private void initThigh() {
        Cylinder cylinder = new Cylinder(20, 20, 0.04f, 0.2f, true);
        thigh = new Geometry("Thigh", cylinder);
        Material mat = new Material(assetManager, "Common/MatDefs/Misc/Unshaded.j3md");
        mat.setColor("Color", ColorRGBA.Brown);
        thigh.setMaterial(mat);
        thighNode = new Node();
        thighNode.attachChild(thigh);
        thighNode.rotate(FastMath.HALF_PI, 0, 0);
        thighNode.setLocalTranslation(0, -0.15f,0); //.,X,y
        hipNode.attachChild(thighNode);
    }
    
    private void initKnee() {
        Cylinder smallCylinder = new Cylinder(20, 20, 0.07f, 0.1f, true);
        knee = new Geometry("Knee", smallCylinder);
        Material mat = new Material(assetManager, "Common/MatDefs/Misc/Unshaded.j3md");
        mat.setColor("Color", ColorRGBA.Red);
        knee.setMaterial(mat);
        kneeNode = new Node();
        kneeNode.attachChild(knee);
        kneeNode.rotate(FastMath.HALF_PI, 0, 0);
        kneeNode.rotate(0, 1.4f, 0);
        kneeNode.setLocalTranslation(0f, 0, 0.15f);
        thighNode.attachChild(kneeNode);
    }
    
    private void initLeg() {
        Cylinder cylinder = new Cylinder(20, 20, 0.03f, 0.50f, true);
        leg = new Geometry("Leg", cylinder);
        Material mat = new Material(assetManager, "Common/MatDefs/Misc/Unshaded.j3md");
        mat.setColor("Color", ColorRGBA.Blue);
        leg.setMaterial(mat);
        legNode = new Node();
        legNode.attachChild(leg);
        legNode.rotate(FastMath.HALF_PI, 0, 0);
        legNode.setLocalTranslation(-0.6f, 0.2f, 0);
        kneeNode.attachChild(legNode);
    }
    
    private void initAnkle() {
        Cylinder smallCylinder = new Cylinder(20, 20, 0.07f, 0.1f, true);
        ankle = new Geometry("Ankle", smallCylinder);
        Material mat = new Material(assetManager, "Common/MatDefs/Misc/Unshaded.j3md");
        mat.setColor("Color", ColorRGBA.Red);
        ankle.setMaterial(mat);
        ankleNode.attachChild(ankle);
        ankleNode.rotate(0, 1.6f,2f);
        ankleNode.setLocalTranslation(0, 0, 0.20f);
        legNode.attachChild(ankleNode);
    }
    
    private void initBase() {
        Cylinder cylinder = new Cylinder(20, 20, 0.03f, 0.60f, true);
        base = new Geometry("Base", cylinder);
        Material mat = new Material(assetManager, "Common/MatDefs/Misc/Unshaded.j3md");
        mat.setColor("Color", ColorRGBA.Green);
        base.setMaterial(mat);
        baseNode.attachChild(base);
        baseNode.setLocalTranslation(0, 0, 0.3f);
        ankleNode.attachChild(baseNode);
    }

}