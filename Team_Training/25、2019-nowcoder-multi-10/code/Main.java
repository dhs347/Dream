import java.math.BigInteger;
import java.util.Scanner;

/*
class CRT {
	BigInteger M, R;
	void exgcd(long a, long b, long &x, long &y) {
		if(b == 0) {
			x = 1; y = 0; return ;
		}
		exgcd(b, a % b, y, x);
		y -= a / b * x;
	}
	long Inv(long a, long mod) {
		long x = 0, y = 0;
		exgcd(a, mod, x, y);
		x %= mod;
		return x < 0 ? x + mod : x;
	}
	long CRT(int n, long *a, long *mod) {
		M = new BigInteger(mod[1]);
		R = new BigInteger(a[1]);
	}
}*/

public class Main {
	static BigInteger M;
	static BigInteger R;
	static BigInteger m;
	static long x, y;
	static int n;
	static int a[] = new int[111];
	static int mod[] = new int[111];
	static void func(BigInteger a, BigInteger b) {
		BigInteger t = a; a = b; b = t;
	}
	/*
	static void exgcd(long a, long b) {
		if(b == 0) { x = 1; y = 0; return ; }
		exgcd(b, a % b);
		long t = x;
		x = y - a / b * x;
		y = t;
	}
	*/
	static void exgcd(long a, long b) {
		if(b == 0) { x = 1; y = 0; return ; }
		long t;
		exgcd(b, a % b);
		t = x; x = y; y = t - a / b * y;
	}
	static long Inv(long a, long mod) {
		x = y = 0;
		exgcd(a, mod);
		x %= mod;
		long ans = (x < 0) ? (x + mod) : x;
		//System.out.println("exgcd " + ans * a % mod);
		return ans;
	}
	public static void main(String[] args) {
		/*
		BigInteger x = BigInteger.valueOf(1);
		BigInteger y = BigInteger.valueOf(2);
		func(x, y);
		System.out.println(x);
		*/
		Scanner cin = new Scanner(System.in);
		n = cin.nextInt();
		m = cin.nextBigInteger();
		for(int i = 1; i <= n; ++i) {
			mod[i] = cin.nextInt(); 
			a[i] = cin.nextInt();
		}
		M = BigInteger.valueOf(mod[1]);
		R = BigInteger.valueOf(a[1]);
		boolean ok = true;
		for(int i = 2; i <= n; ++i) {
			BigInteger mi = BigInteger.valueOf(mod[i]);
			int g = M.gcd(mi).intValue();
			BigInteger ai = BigInteger.valueOf(a[i]);
			BigInteger bg = BigInteger.valueOf(g);
			BigInteger air = ai.subtract(R);
			long inv = Inv(( M.divide(bg).mod(BigInteger.valueOf(mod[i] / g)) ).longValue(), mod[i] / g);
			if(!((air.mod(bg).equals(BigInteger.ZERO)))) {
				ok = false;
				break;
			}
			BigInteger bi = BigInteger.valueOf(inv);
			R = R.add(bi.multiply(air.divide(bg)).mod(mi.divide(bg)).multiply(M));
			M = M.divide(bg).multiply(mi);
			R = (R.mod(M).add(M)).mod(M);
		}
		//System.out.println(R);
		if(ok) {
			if(R.compareTo(m) < 0) {
				System.out.println(R);
			} else {
				System.out.println("he was probably lying");
			}
		} else {
			System.out.println("he was definitely lying");
		}
	}

}
/*
 3 100
 3 2
 5 3
 7 2
 
 4 10000
 12 7
 15 2
 30 5
 8 6
 
 2 10
 11 3
 19 7
 */

