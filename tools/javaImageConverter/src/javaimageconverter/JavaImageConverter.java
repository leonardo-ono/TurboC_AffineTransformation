/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package javaimageconverter;

import java.awt.Color;
import java.awt.image.BufferedImage;
import java.io.FileOutputStream;
import java.util.HashMap;
import java.util.Map;
import javax.imageio.ImageIO;

/**
 *
 * @author leonardo
 */
public class JavaImageConverter {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws Exception {
        //for (int i=0; i<256; i++) {
        //    System.out.println("\tdb 0, 0, 0 ; " + i);
        //}
        gerar();
    }
    
    public static void gerar() throws Exception {
        BufferedImage image = ImageIO.read(JavaImageConverter.class.getResourceAsStream("sprite.bmp"));
        System.out.println("width: " + image.getWidth());
        System.out.println("height: " + image.getHeight());
        
        String path = "E:/Leo/apps/c/g/";
        //path = "/media/Novo volume/Leo/apps/c/g/";
        
        String filename = "test";
        
        FileOutputStream fos = new FileOutputStream(path + filename + ".img");
        
        int c1 = image.getWidth() & 0xFF;
        int c2 = (image.getWidth() & 0xFF00) >> 8;
        int c3 = image.getHeight() & 0xFF;
        int c4 = (image.getHeight() & 0xFF00) >> 8;
        
        // write size
        fos.write(c1);
        fos.write(c2);
        fos.write(c3);
        fos.write(c4);
        
        // write data
        
        Map<Color, Integer> colors = new HashMap<Color, Integer>();
        int colorIndex = 0;
        
        for (int y = 0; y < image.getHeight(); y++) {
            for (int x = 0; x < image.getWidth(); x++) {
                Color color = new Color(image.getRGB(x, y));
                Integer index = colors.get(color);
                if (index == null) {
                    index = colorIndex++;
                    colors.put(color, index);
                }
                fos.write(index);
            }
        }
        fos.close();
        
        // write palette 
        
        System.out.println("colors count:" + colors.size());
        
        Map<Integer, Color> colorsIndex = new HashMap<Integer, Color>();
        
        for (Color colorKey : colors.keySet()) {
            Integer index = colors.get(colorKey);
            colorsIndex.put(index, colorKey);
        }

        fos = new FileOutputStream(path + filename + ".pal");
        
        for (int c = 0; c < 256; c++) {
            Color color = colorsIndex.get(c);
            int r = 0;
            int g = 0;
            int b = 0;
            if (color != null) {
                r = (int) ((color.getRed() / 255.0) * 63);
                g = (int) ((color.getGreen() / 255.0) * 63);
                b = (int) ((color.getBlue() / 255.0) * 63);
                r = color.getRed();
                g = color.getGreen();
                b = color.getBlue();
            }
            System.out.println("color " + c + " ->" + r + " " + g + " " + b);
            fos.write(r);
            fos.write(g);
            fos.write(b);
        }
        
        fos.close();
    }
    
}
