package hexopod;

import com.jme3.asset.AssetManager;
import com.jme3.material.Material;
import com.jme3.math.ColorRGBA;
import com.jme3.math.FastMath;
import com.jme3.math.Vector3f;
import com.jme3.scene.Geometry;
import com.jme3.scene.Node;
import com.jme3.scene.shape.Cylinder;

public class Leg extends Node {

    private Geometry hip;   //servo         :heup
    private Geometry thigh; //beenonderdeel :Bovenbeen
    private Geometry knee;  //servo         :Knie
    private Geometry leg;   //beenonderdeel :Onderbeen
    private Geometry ankle; //servo         :enkel
    private Geometry base;  //beenonderdeel :voet
    
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
        }

        initHip();
        initThigh();
        //initKnee();
        //initLeg();
        //initAnkle();
        //initBase();
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
    
    private void setupParts() {
        
        //Rotation
        hip.rotate(FastMath.HALF_PI, 0, 0);
        
        //Translation
        thigh.setLocalTranslation(new Vector3f(0, 0.05f, 0.15f));
    }

    private void initHip() {
        Cylinder smallCylinder = new Cylinder(10, 10, 0.05f, 0.2f, true);
        hip = new Geometry("Hip", smallCylinder);
        Material mat = new Material(assetManager, "Common/MatDefs/Misc/Unshaded.j3md");
        mat.setColor("Color", ColorRGBA.Blue);
        hip.setMaterial(mat);
        this.attachChild(hip);
    }
    
    private void initThigh() {
        Cylinder cylinder = new Cylinder(20, 20, 0.07f, 0.4f, true);
        thigh = new Geometry("Thigh", cylinder);
        Material mat = new Material(assetManager, "Common/MatDefs/Misc/Unshaded.j3md");
        mat.setColor("Color", ColorRGBA.Green);
        thigh.setMaterial(mat);
        this.attachChild(thigh);
    }
    
    private void initKnee() {
        Cylinder smallCylinder = new Cylinder(10, 10, 0.05f, 0.12f, true);
        knee = new Geometry("Knee", smallCylinder);
        Material mat = new Material(assetManager, "Common/MatDefs/Misc/Unshaded.j3md");
        mat.setColor("Color", ColorRGBA.Blue);
        knee.setMaterial(mat);
        this.attachChild(knee);
    }
    
    private void initLeg() {
        Cylinder cylinder = new Cylinder(20, 20, 0.12f, 0.35f, true);
        leg = new Geometry("Leg", cylinder);
        Material mat = new Material(assetManager, "Common/MatDefs/Misc/Unshaded.j3md");
        mat.setColor("Color", ColorRGBA.Green);
        leg.setMaterial(mat);
        this.attachChild(leg);
    }
    
    private void initAnkle() {
        Cylinder smallCylinder = new Cylinder(10, 10, 0.05f, 0.12f, true);
        ankle = new Geometry("Ankle", smallCylinder);
        Material mat = new Material(assetManager, "Common/MatDefs/Misc/Unshaded.j3md");
        mat.setColor("Color", ColorRGBA.Blue);
        ankle.setMaterial(mat);
        this.attachChild(ankle);
    }
    
    private void initBase() {
        Cylinder cylinder = new Cylinder(20, 20, 0.12f, 0.35f, true);
        base = new Geometry("Base", cylinder);
        Material mat = new Material(assetManager, "Common/MatDefs/Misc/Unshaded.j3md");
        mat.setColor("Color", ColorRGBA.Green);
        base.setMaterial(mat);
        this.attachChild(base);
    }
}
