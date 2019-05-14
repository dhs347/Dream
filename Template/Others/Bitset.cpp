// Base
	b.any();   // has 1 ?
	b.none();  // all 0 ?
	b.count(); // cnt of 1
	
	b.set();   // all to 1
	b.reset(); // all to 0
	b.flip();  // all = 0 <-> 1

	b.set(p);  // b[p] = 1
	b.test(p); // b[p] is 1
	b.reset(p);// b[p] = 0
	b.flip(p); // b[p] = 0 <-> 1

// Black tech
	// __builtin_ctz in bitst
	b._Find_first();  

	// travel all 1
	for (int i = b._Find_first(); i < sz(b); i = b._Find_next(i)); 