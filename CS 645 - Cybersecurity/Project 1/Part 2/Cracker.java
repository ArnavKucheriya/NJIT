/**
 * CS 645 - Spring 2026 - Project 1 - Problem 1 Part 2
 * Team member(s): 
 *      Arnav Kucheriya (ak2945@njit.edu)
 *      Francis Reyes (fdr7@njit.edu)
 *      Grimm Cato (gc359@njit.edu)
 *
 * Cracker.java
 * Dictionary attack against Linux-style shadow entries:
 *   username:$1$salt$hash:...other fields
 *
 * Requires MD5Shadow.java (provided by the course) in the SAME directory.
 * Expected files in the SAME directory:
 *   - shadow
 *   - common-passwords.txt
 *
 * Output (one per line):
 *   username:password
 */
import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class Cracker {

    public static void main(String[] args) {
        File shadowFile = new File("shadow");
        File dictFile = new File("common-passwords.txt");

        if (!shadowFile.isFile() || !dictFile.isFile()) {
            System.err.println("Missing input files. Put shadow and common-passwords.txt in the same folder.");
            System.exit(1);
        }

        // MD5Shadow.java must be present/compiled too.
        // It must provide: public static String crypt(String password, String salt)
        // where salt is the 8-char salt (no $1$ prefix).
        List<String> passwords = loadDictionary(dictFile);

        try (BufferedReader br = new BufferedReader(new FileReader(shadowFile))) {
            String line;
            while ((line = br.readLine()) != null) {
                line = line.trim();
                if (line.isEmpty() || line.startsWith("#")) continue;

                // Format: username:shash:... (we only need first 2 fields)
                String[] fields = line.split(":", 3);
                if (fields.length < 2) continue;

                String username = fields[0];
                String shash = fields[1];

                ShadowHash parsed = parseShadowHash(shash);
                if (parsed == null) continue;

                String found = crackShadow(username, parsed, passwords);
                if (found != null) {
                    System.out.println(username + ":" + found);
                }
            }
        } catch (IOException e) {
            System.err.println("Error reading shadow: " + e.getMessage());
            System.exit(2);
        }
    }

private static List<String> loadDictionary(File dictFile) {
    List<String> out = new ArrayList<>();
    try (BufferedReader br = new BufferedReader(new FileReader(dictFile))) {
        String line;
        while ((line = br.readLine()) != null) {
            line = line.trim();
            if (!line.isEmpty()) {
                out.add(line);
            }
        }
    } catch (IOException e) {
        System.err.println("Error reading common-passwords.txt: " + e.getMessage());
        System.exit(2);
    }
    return out;
}

private static String crackShadow(String username, ShadowHash parsed, List<String> passwords) {
    for (String pw : passwords) {
        try {
            String computedHash = MD5Shadow.crypt(pw, parsed.salt);
            if (computedHash != null && computedHash.equals(parsed.hash)) {
                return pw;
            }
        } catch (RuntimeException ex) {
            // Skip candidates that trigger MD5Shadow’s internal bug
            continue;
        }
    }
    return null;
}

    private static ShadowHash parseShadowHash(String shash) {
        // expected: $1$salt$hash  (salt can be up to 8 chars in typical /etc/shadow MD5)
        if (shash == null) return null;
        shash = shash.trim();
        if (!shash.startsWith("$1$")) return null;

        String[] parts = shash.split("\\$");
        // splitting "$1$salt$hash" gives: ["", "1", "salt", "hash"]
        if (parts.length < 4) return null;

        String salt = parts[2];
        String hash = parts[3];
        return new ShadowHash(salt, hash);
    }

    private static class ShadowHash {
        final String salt;
        final String hash;
        ShadowHash(String salt, String hash) {
            this.salt = salt;
            this.hash = hash;
        }
    }
}
