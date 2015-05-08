package hexopod;

import com.jme3.asset.AssetManager;
import com.jme3.material.Material;
import com.jme3.math.ColorRGBA;
import com.jme3.math.FastMath;
import com.jme3.math.Quaternion;
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
        this.id =id;
        assetManager = assetmanager;
        init();
        setupParts();  
    }
    private void init(){
        initNodes();
        initHip();
        initThigh();
        initKnee();
        initLeg();
        initAnkle();
        initBase();                                  
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
    
    
    /*
     * initialize Nodes for each part of the leg
     */
    private void initNodes() {
        
        hipNode = new Node();
        thighNode = new Node();
        kneeNode = new Node();
        legNode = new Node();
        ankleNode = new Node();
        baseNode = new Node();
        
    }
    
    private void setupParts() {
            switch (id) {
            case 1:
                hipNode.rotate(0, 0, 3.2f);
                hipNode.setLocalTranslation(0.1f, 0, 0);
                break;
            case 2:
                hipNode.rotate(0, 0, 3.2f);
                hipNode.setLocalTranslation(0.1f, 0, 0);
                break;
            case 3:
                hipNode.rotate(0, 0, 3.2f);
                hipNode.setLocalTranslation(0.1f, 0, 0);
                break;
            case 4:
                hipNode.rotate(0, 0, 0f);
                hipNode.setLocalTranslation(-0.1f, 0, 0);
                break;
            case 5:
                hipNode.rotate(0, 0, 0f);
                hipNode.setLocalTranslation(-0.1f, 0, 0);
                break;
            case 6:
                hipNode.rotate(0, 0, 0f);
                hipNode.setLocalTranslation(-0.1f, 0, 0);
                break;                    
        }    
        this.attachChild(hipNode); 
        }
        

    private void initHip() {
        Cylinder smallCylinder = new Cylinder(20, 20, 0.07f, 0.1f, true);
        hip = new Geometry("Hip", smallCylinder);
        Material mat = new Material(assetManager, "Common/MatDefs/Misc/Unshaded.j3md");
        mat.setColor("Color", ColorRGBA.Orange);
        hip.setMaterial(mat);
        hipNode.attachChild(hip);
        hipNode.setLocalTranslation(-0.1f, 0, 0);
        hipNode.rotate(FastMath.HALF_PI, 0f, 0);
        hipNode.rotate(0, 0, -1.6f);
        hipNode.attachChild(thighNode);
    }
    
    private void initThigh() {
        Cylinder cylinder = new Cylinder(20, 20, 0.04f, 0.2f, true);
        thigh = new Geometry("Thigh", cylinder);
        Material mat = new Material(assetManager, "Common/MatDefs/Misc/Unshaded.j3md");
        mat.setColor("Color", ColorRGBA.Orange);
        thigh.setMaterial(mat);
        thighNode.attachChild(thigh);
        thighNode.rotate(FastMath.HALF_PI, 0, 0);
        thighNode.setLocalTranslation(0, -0.15f,0); //.,X,y
        thighNode.attachChild(kneeNode);
    }
    
    private void initKnee() {
        Cylinder smallCylinder = new Cylinder(20, 20, 0.07f, 0.1f, true);
        knee = new Geometry("Knee", smallCylinder);
        Material mat = new Material(assetManager, "Common/MatDefs/Misc/Unshaded.j3md");
        mat.setColor("Color", ColorRGBA.Green);
        knee.setMaterial(mat);
        kneeNode.attachChild(knee);
        kneeNode.rotate(FastMath.ZERO_TOLERANCE, 1.5f, 0);
        kneeNode.rotate(0,0,2.5f);
        kneeNode.setLocalTranslation(0f, 0, 0.15f);
    }
    
    private void initLeg() {
        Cylinder cylinder = new Cylinder(20, 20, 0.03f, 0.50f, true);
        leg = new Geometry("Leg", cylinder);
        Material mat = new Material(assetManager, "Common/MatDefs/Misc/Unshaded.j3md");
        mat.setColor("Color", ColorRGBA.Green);
        leg.setMaterial(mat);
        legNode.attachChild(leg);
        kneeNode.attachChild(legNode);
        legNode.setLocalTranslation(-0.02f, 0.25f, 0.0f);
        legNode.rotateUpTo(Vector3f.UNIT_Y);
        legNode.rotate(1.5f, 1.5f, 0);
        kneeNode.attachChild(legNode);
    }
    
    private void initAnkle() {
        Cylinder smallCylinder = new Cylinder(20, 20, 0.07f, 0.1f, true);
        ankle = new Geometry("Ankle", smallCylinder);
        Material mat = new Material(assetManager, "Common/MatDefs/Misc/Unshaded.j3md");
        mat.setColor("Color", ColorRGBA.Red);
        ankle.setMaterial(mat);
        ankleNode.attachChild(ankle);
        ankleNode.rotate(FastMath.ZERO_TOLERANCE, 1.5f, 0);
        ankleNode.rotate(0,0,6.5f);
        ankleNode.setLocalTranslation(0f, 0, -0.30f);     
        legNode.attachChild(ankleNode);
    }
    
    private void initBase() {
        Cylinder cylinder = new Cylinder(20, 20, 0.03f, 0.90f, true);
        base = new Geometry("Base", cylinder);
        Material mat = new Material(assetManager, "Common/MatDefs/Misc/Unshaded.j3md");
        mat.setColor("Color", ColorRGBA.Red);
        base.setMaterial(mat);
        baseNode.attachChild(base);
        baseNode.setLocalTranslation(-0.02f, 0.45f, 0.0f);
        baseNode.rotateUpTo(Vector3f.UNIT_Y);
        baseNode.rotate(1.5f, 1.5f, 0);
        ankleNode.attachChild(baseNode);
    }

}