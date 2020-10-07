public class Decrypt {
    public static void decodeAndSave(byte[] buf, String path) throws IOException {
        ArrayList<Integer> seq = new ArrayList<>();
        generateLFSR("a271730728cbe141e47fd9d677e9006d", seq);
        FileOutputStream fos = new FileOutputStream(path);
        for(int i = 0; i<128;i++){
            buf[i] = (byte) xorByte(buf[i], seq);
        }
        fos.write(buf);
        fos.close();
    }

    public static void generateLFSR(String key, ArrayList<Integer> seq) {
        byte[] keySet = (key + key).getBytes();

        seq.add(0, 301989938);
        seq.add(1, 623357073);
        seq.add(2, -2004086252);


        for (int i = 0; i < 4; ++i) {
            seq.set(0, keySet[i] | (seq.get(0) << 8));
            seq.set(1, keySet[4 + i] | (seq.get(1) << 8));
            seq.set(2, keySet[8 + i] | (seq.get(2) << 8));
        }
    }

    public static int xorByte(int b, ArrayList<Integer> seq) {
        char flag1=1;
        char flag2=0;

        int result=0;

        for (int i = 0; i < 8; i++) {
            int v10 = seq.get(0) >>> 1;
            if ((seq.get(0) << 31) != 0) {
                seq.set(0, v10 ^ 0xC0000031);
                int v12 = seq.get(1) >> 1;
                if (seq.get(1) << 31 != 0) {
                    seq.set(1, (v12 | 0xC0000000) ^ 0x20000010);
                    flag1 = 1;
                } else {
                    seq.set(1, v12 & 0x3FFFFFFF);
                    flag1 = 0;
                }
            } else {
                seq.set(0, v10);
                int v11 = seq.get(2) >> 1;
                if (seq.get(2) << 31 != 0) {
                    seq.set(2, (v11 | 0xF0000000) ^ 0x8000001);
                    flag2 = 1;
                } else {
                    seq.set(2, v11 & 0xFFFFFFF);
                    flag2 = 0;
                }
            }
            result = (flag1 ^ flag2 | 2 * result);
        }
        result = result ^ b;
        return result;
    }
}
