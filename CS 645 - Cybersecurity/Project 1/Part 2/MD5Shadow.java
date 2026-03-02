/*******
* Prepared for Project 1, CS 645, Fall 2020, NJIT
*******/


import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class MD5Shadow
{

    /** magic is 1 for MD5 */
    private static String magic = "$1$";
    
    /** Characters for base64 encoding */
    private static String char64 = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    private static byte[] Concat(byte[] array1, byte[] array2)
    {
        byte[] concat = new byte[array1.length + array2.length];
        for (int i = 0; i < concat.length; i++)
        {
            if (i < array1.length)
            {
                concat[i] = array1[i];
            }
            else
            {
                concat[i] = array2[i - array1.length];
            }
        }
        return concat;
    }

    private static byte[] PartialConcat(byte[] array1, byte[] array2, int max)
    {
        byte[] concat = new byte[array1.length + max];

        for (int i = 0; i < concat.length; i++)
        {
            if (i < array1.length)
            {
                concat[i] = array1[i];
            }
            else
            {
                concat[i] = array2[i - array1.length];
            }
        }
        return concat;
    }

    //This method would convert an value to the Base64 string
    private static String to64(int value, int length)
    {
        StringBuffer result;

        result = new StringBuffer();
        while (--length >= 0)
        {
            int ind = value & 0x3f;
            result.append(char64.substring(ind, ind + 1));
            value >>= 6;
        }
        return (result.toString());
    }
    
    public static String crypt(String password, String salt)
    {
        int saltEnd;
        int value;
        int i;

        byte[] pwBytes = null;
        byte[] saltBytes = null;
        byte[] ctx = null;
        byte[] ctx2 = null;

        StringBuilder result;
        MessageDigest hashGenerator = null;
        try
        {
            //initialize the MD5 hash generator
            hashGenerator = MessageDigest.getInstance("MD5");
        }
        catch (NoSuchAlgorithmException ex)
        {
            ex.printStackTrace();
        }

////////////////////////////////////////Some safety checks.... can be omitted..................
        // Skip magic if it exists with the salt..... checking for accidentally using along with magic
        if (salt.startsWith(magic))salt = salt.substring(magic.length());
        
        // Remove password hash if present..... checking for accidentally using along with pw
        if ((saltEnd = salt.lastIndexOf('$')) != -1)salt = salt.substring(0, saltEnd);
        
        // Shorten the salt to 8 characters if it is longer.......... assuming the salt must be 8 chars long
        if (salt.length() > 8)
        {
            salt = salt.substring(0, 8);
        }
///////////////////////////////////////////////////////////////////////////////////////////////

        ctx = (password + magic + salt).getBytes();
        ctx2 = hashGenerator.digest((password + salt + password).getBytes());


        /////////I am commenting out this one.... But for longer passwords, it should have to be enabled....
        
//        for (ind = password.length(); ind > 0; ind -= 16)
//        {
//            if (ind > 16)
//            {
//                ctx = Concat(ctx, ctx2);
//            }
//            else
//            {
//                ctx = PartialConcat(ctx, ctx2, ind);
//            }
//        }

        ctx = PartialConcat(ctx, ctx2, password.length());

        
        pwBytes = password.getBytes();

        //This is the equivalent of the while loop in the C code
        for (i = password.length(); i > 0; i >>= 1)
        {
            if ((i & 1) == 1)
            {
                ctx = Concat(ctx, new byte[]{0});
            }
            else
            {
                ctx = Concat(ctx, new byte[]{pwBytes[0]});
            }
        }

        ctx2 = hashGenerator.digest(ctx);

        byte[] ctx1;

        
        saltBytes = salt.getBytes();
        
        // Do some scramblings or mutations?!!
        for (i = 0; i < 1000; i++)
        {
            ctx1 = new byte[]
            {
            };
            if ((i & 1) == 1)
            {
                ctx1 = Concat(ctx1, pwBytes);
            }
            else
            {
                ctx1 = Concat(ctx1, ctx2);
            }
            if (i % 3 != 0)
            {
                ctx1 = Concat(ctx1, saltBytes);
            }
            if (i % 7 != 0)
            {
                ctx1 = Concat(ctx1, pwBytes);
            }
            if ((i & 1) != 0)
            {
                ctx1 = Concat(ctx1, ctx2);
            }
            else
            {
                ctx1 = Concat(ctx1, pwBytes);
            }
            ctx2 = hashGenerator.digest(ctx1);
        }
        result = new StringBuilder();

        // Do the shifting and add the Base64 converted hash to the result string
        value = ((ctx2[0] & 0xff) << 16) | ((ctx2[6] & 0xff) << 8) | (ctx2[12] & 0xff);
        result.append(to64(value, 4));
        value = ((ctx2[1] & 0xff) << 16) | ((ctx2[7] & 0xff) << 8) | (ctx2[13] & 0xff);
        result.append(to64(value, 4));
        value = ((ctx2[2] & 0xff) << 16) | ((ctx2[8] & 0xff) << 8) | (ctx2[14] & 0xff);
        result.append(to64(value, 4));
        value = ((ctx2[3] & 0xff) << 16) | ((ctx2[9] & 0xff) << 8) | (ctx2[15] & 0xff);
        result.append(to64(value, 4));
        value = ((ctx2[4] & 0xff) << 16) | ((ctx2[10] & 0xff) << 8) | (ctx2[5] & 0xff);
        result.append(to64(value, 4));
        value = ctx2[11] & 0xff;
        result.append(to64(value, 2));

//        return magic + salt + "$" + result.toString();
        return result.toString();
    }
}
