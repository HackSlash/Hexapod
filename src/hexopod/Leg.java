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
    
    private int id;
    private AssetManager assetManager;

    public Leg(int id, AssetManager assetmanager) {
        
        assetManager = assetmanager;
        
        switch (id) {
            case 1:
                initHip();
                break;
            case 2:
                initThigh();
                break;
            case 3:
                initKnee();
                break;
            case 4:
                initLeg();
                break;
            case 5:
                initAnkle();
                break;
            case 6:
                initBase();
                break;
        }
     //   setupParts();
        

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
      //  hip.rotate(FastMath.HALF_PI, 0, 0);
          thigh.rotate(FastMath.PI,1.5f,0);
        //Translation
        hip.setLocalTranslation(-0.1f, 0.2f, 0);
        thigh.setLocalTranslation(new Vector3f(-0.3f, 0.2f, 0f));
    //    knee.setLocalTranslation(new Vector3f(0, 1f,0.15f));
    }

    private void initHip() {
        Cylinder smallCylinder = new Cylinder(20, 20, 0.07f, 0.1f, true);
        hip = new Geometry("Hip", smallCylinder);
        Material mat = new Material(assetManager, "Common/MatDefs/Misc/Unshaded.j3md");
        mat.setColor("Color", ColorRGBA.BlackNoAlpha);
        hip.setMaterial(mat);
        hip.rotate(FastMath.HALF_PI, 0, 0);
        this.attachChild(hip);
    }
    
    private void initThigh() {
        Cylinder cylinder = new Cylinder(20, 20, 0.04f, 0.2f, true);
        thigh = new Geometry("Thigh", cylinder);
        Material mat = new Material(assetManager, "Common/MatDefs/Misc/Unshaded.j3md");
        mat.setColor("Color", ColorRGBA.Brown);
        thigh.setMaterial(mat);
        this.attachChild(thigh);
    }
    
    private void initKnee() {
        Cylinder smallCylinder = new Cylinder(20, 20, 0.07f, 0.1f, true);
        knee = new Geometry("Knee", smallCylinder);
        Material mat = new Material(assetManager, "Common/MatDefs/Misc/Unshaded.j3md");
        mat.setColor("Color", ColorRGBA.BlackNoAlpha);
        knee.setMaterial(mat);
        knee.rotate(0, 1.6f,2f);
        this.attachChild(knee);
    }
    
    private void initLeg() {
        Cylinder cylinder = new Cylinder(20, 20, 0.03f, 0.40f, true);
        leg = new Geometry("Leg", cylinder);
        Material mat = new Material(assetManager, "Common/MatDefs/Misc/Unshaded.j3md");
        mat.setColor("Color", ColorRGBA.Brown);
        leg.setMaterial(mat);
        this.attachChild(leg);
    }
    
    private void initAnkle() {
        Cylinder smallCylinder = new Cylinder(20, 20, 0.07f, 0.1f, true);
        ankle = new Geometry("Ankle", smallCylinder);
        Material mat = new Material(assetManager, "Common/MatDefs/Misc/Unshaded.j3md");
        mat.setColor("Color", ColorRGBA.BlackNoAlpha);
        ankle.setMaterial(mat);
        ankle.rotate(0, 1.6f,2f);
        this.attachChild(ankle);
    }
    
    private void initBase() {
        Cylinder cylinder = new Cylinder(20, 20, 0.03f, 0.60f, true);
        base = new Geometry("Base", cylinder);
        Material mat = new Material(assetManager, "Common/MatDefs/Misc/Unshaded.j3md");
        mat.setColor("Color", ColorRGBA.Brown);
        base.setMaterial(mat);
        this.attachChild(base);
    }

}