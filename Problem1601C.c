    #include <stdio.h>
    #include <string.h>
    #include <sys/time.h>
     
    #define N	1000000
    #define M	1000000
     
    unsigned int X = 12345;
     
    void srand_() {
    	struct timeval tv;
     
    	gettimeofday(&tv, NULL);
    	X = tv.tv_sec ^ tv.tv_usec | 1;
    }
     
    int rand_() {
    	return (X *= 3) >> 1;
    }
     
    int aa[N], bb[M];
     
    int *cc;
     
    void sort(int *ii, int l, int r) {
    	while (l < r) {
    		int i = l, j = l, k = r, i_ = ii[l + rand_() % (r - l)], tmp;
     
    		while (j < k) {
    			int c = cc[ii[j]] != cc[i_] ? cc[ii[j]] - cc[i_] : ii[j] - i_;
     
    			if (c == 0)
    				j++;
    			else if (c < 0) {
    				tmp = ii[i], ii[i] = ii[j], ii[j] = tmp;
    				i++, j++;
    			} else {
    				k--;
    				tmp = ii[j], ii[j] = ii[k], ii[k] = tmp;
    			}
    		}
    		sort(ii, l, i);
    		l = k;
    	}
    }
     
    int ft[N];
     
    void update(int i, int n) {
    	while (i < n) {
    		ft[i]++;
    		i |= i + 1;
    	}
    }
     
    int query(int i) {
    	int x = 0;
     
    	while (i >= 0) {
    		x += ft[i];
    		i &= i + 1, i--;
    	}
    	return x;
    }
     
    int xx[N * 2], pq[N * 2], iq[1 + N + 1], cnt;
     
    int lt(int i, int j) { return xx[i] > xx[j]; }
     
    int p2(int p) {
    	return (p *= 2) > cnt ? 0 : (p < cnt && lt(iq[p + 1], iq[p]) ? p + 1 : p);
    }
     
    void pq_up(int i) {
    	int p, q, j;
     
    	for (p = pq[i]; (q = p / 2) && lt(i, j = iq[q]); p = q)
    		iq[pq[j] = p] = j;
    	iq[pq[i] = p] = i;
    }
     
    void pq_dn(int i) {
    	int p, q, j;
     
    	for (p = pq[i]; (q = p2(p)) && lt(j = iq[q], i); p = q)
    		iq[pq[j] = p] = j;
    	iq[pq[i] = p] = i;
    }
     
    void pq_add(int i) {
    	pq[i] = ++cnt, pq_up(i);
    }
     
    int pq_remove_first() {
    	int i = iq[1], j = iq[cnt--];
     
    	if (j != i)
    		pq[j] = 1, pq_dn(j);
    	pq[i] = 0;
    	return i;
    }
     
    int main() {
    	int t;
     
    	srand_();
    	scanf("%d", &t);
    	while (t--) {
    		static int ii[N], jj[M];
    		int n, m, i, j;
    		long long ans;
     
    		scanf("%d%d", &n, &m);
    		for (i = 0; i < n; i++) {
    			scanf("%d", &aa[i]);
    			ii[i] = i;
    		}
    		cc = aa, sort(ii, 0, n);
    		for (j = 0; j < m; j++) {
    			scanf("%d", &bb[j]);
    			jj[j] = j;
    		}
    		cc = bb, sort(jj, 0, m);
    		memset(ft, 0, n * sizeof *ft);
    		ans = 0;
    		for (i = n - 1; i >= 0; i--) {
    			ans += query(ii[i]);
    			update(ii[i], n);
    		}
    		for (i = 0, j = 0; i < n; i++) {
    			while (j < m && bb[jj[j]] < aa[ii[i]])
    				j++;
    			xx[ii[i] << 1 | 0] = j;
    		}
    		for (i = 0, j = 0; i < n; i++) {
    			while (j < m && bb[jj[j]] <= aa[ii[i]])
    				j++;
    			xx[ii[i] << 1 | 1] = j;
    		}
    		memset(pq, 0, n * 2 * sizeof *pq), cnt = 0;
    		for (i = 0; i < n; i++) {
    			int x;
     
    			pq_add(i << 1 | 0), pq_add(i << 1 | 1);
    			x = xx[pq_remove_first()];
    			if (x < xx[i << 1 | 0])
    				ans += xx[i << 1 | 0] - x;
    			else if (x > xx[i << 1 | 1])
    				ans += x - xx[i << 1 | 1];
    		}
    		printf("%lld\n", ans);
    	}
    	return 0;
    }
