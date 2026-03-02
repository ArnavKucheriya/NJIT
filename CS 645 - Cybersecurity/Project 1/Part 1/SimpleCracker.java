/**
 * CS 645 - Spring 2026 - Project 1 - Problem 1 Part 1
 * Team member(s): 
 *      Arnav Kucheriya (ak2945@njit.edu)
 *      Francis Reyes (fdr7@njit.edu)
 *      Grimm Cato (gc359@njit.edu)
 * 
 * SimpleCracker.java
 * Dictionary attack against "shadow-simple" where hash = MD5(salt + password)
 *
 * Expected files in the SAME directory:
 *   - shadow-simple
 *   - common-passwords.txt
 *
 * Output (one per line):
 *   username:password
 */
import java.io.*;
import java.math.BigInteger;
import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.util.ArrayList;
import java.util.List;

public class SimpleCracker {

    public static void main(String[] args) {
        File shadowFile = new File("shadow-simple");
        File dictFile = new File("common-passwords.txt");

        if (!shadowFile.isFile() || !dictFile.isFile()) {
            System.err.println("Missing input files. Put shadow-simple and common-passwords.txt in the same folder.");
            System.exit(1);
        }

        List<String> passwords = loadDictionary(dictFile);

        try (BufferedReader br = new BufferedReader(new FileReader(shadowFile))) {
            String line;
            while ((line = br.readLine()) != null) {
                line = line.trim();
                if (line.isEmpty() || line.startsWith("#")) continue;

                // Format: username:salt:hash
                String[] parts = line.split(":", 3);
                if (parts.length != 3) continue;

                String username = parts[0];
                String salt = parts[1];
                String targetHash = parts[2].trim().toUpperCase();

                String found = crackSimpleMD5(salt, targetHash, passwords);
                if (found != null) {
                    System.out.println(username + ":" + found);
                }
            }
        } catch (IOException e) {
            System.err.println("Error reading shadow-simple: " + e.getMessage());
            System.exit(2);
        }
    }

    private static List<String> loadDictionary(File dictFile) {
        List<String> out = new ArrayList<>();
        try (BufferedReader br = new BufferedReader(new FileReader(dictFile))) {
            String line;
            while ((line = br.readLine()) != null) {
                line = line.trim();
                if (!line.isEmpty()) out.add(line);
            }
        } catch (IOException e) {
            System.err.println("Error reading common-passwords.txt: " + e.getMessage());
            System.exit(2);
        }
        return out;
    }

    private static String crackSimpleMD5(String salt, String targetHex, List<String> passwords) {
        for (String pw : passwords) {
            String candidate = salt + pw;
            String hex = md5Hex(candidate);
            if (hex.equalsIgnoreCase(targetHex)) return pw;
        }
        return null;
    }

    private static String md5Hex(String s) {
        try {
            MessageDigest md = MessageDigest.getInstance("MD5");
            byte[] digest = md.digest(s.getBytes(StandardCharsets.UTF_8));
            return toHex(digest); // returns uppercase
        } catch (Exception e) {
            throw new RuntimeException("MD5 not available?", e);
        }
    }

    // Provided by the assignment prompt
    public static String toHex(byte[] bytes) {
        BigInteger bi = new BigInteger(1, bytes);
        return String.format("%0" + (bytes.length << 1) + "X", bi);
    }
}
