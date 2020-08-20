#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int inlineSubtraction(int a, int b);
int inlineAddition(int a, int b);

int cmpfunc(const void *a, const void *b)
{
	return (*(int*) a - *(int*) b);
}

int main(int argc, char **argv)
{
	int k, p, z, l, t, nxtf, s, inc, n, fir, f, no, ac;
	register int i, j;
	inc = 1;
	j = i = n = p = k = nxtf = no = fir = 0;
	ac = 48;

	int inlineSubtraction(int a, int b)	//Einlesen von Integer "a" und "b"
	{
		__asm__
			(				"subl %%ebx, %%eax;"	// eax-ebx, sprich a-b
				: "=a"(a)	// Output eax=a. Sprich a-b=a
				: "a"(a), "b"(b)	//"a" in Register eax und "b" in ebx
		);
		return a;	//Ausgabe von a
	}

	int inlineAddition(int a, int b)
	{
		__asm__
			(				"addl %%ebx, %%eax;": "=a"(a): "a"(a), "b"(b)
		);
		return a;
	}

	char temp1;

	FILE * fp;
	fp = fopen(argv[1], "r");

	while ((temp1 = getc(fp)) != EOF)
	{

		if ((temp1 == 32 || temp1 == 10) && (no == 0))
		{
			n++;
		}
		if ((temp1 == 32) && (no == 1))
		{
			k++;
		}
		if (temp1 == 10)
		{
			no++;
			if (no == 2) /
			{
				fprintf(stderr, "Error: Es sind exakt 2 Zeilen erlaubt.");
				return EXIT_FAILURE;
			}
		}
	}

	fclose(fp);
	k++;

	int *c = (int*) malloc(n *(sizeof(*c)));
	int *g = (int*) malloc(k *(sizeof(*g)));
	int *g_m = (int*) malloc(k *(sizeof(*g_m)));

	char temp;
	int tomp;
	no = n = k = fir = 0;

	FILE * fp1;
	fp1 = fopen(argv[1], "r");

	if (fp1 == NULL)
	{
		printf("Datei konnte nicht geoeffnet werden.\n");
	}
	else
	{
		while ((temp = getc(fp1)) != EOF)

		{

			if ((fir == 1) && (no == 0) && (temp != 32) && (temp != 10))	// C einlesen 
			{ 
				tomp = inlineSubtraction(temp, ac);
				c[n] = c[n] *10;
				tomp = inlineSubtraction(temp, ac);
				c[n] = inlineAddition(c[n], tomp);
			}
			else if ((fir == 0) && (no == 0) && (temp != 32) && (temp != 10))
			{
				c[n] = temp;
				c[n] = inlineSubtraction(c[n], ac);
				fir = 1;
			}
			else if ((temp == 32 || temp == 10) && (no == 0))
			{
				n++;
				fir = 0;
			}

			if ((no == 0) && (temp < 48 || temp > 57) && (temp != 10) && (temp != 32))
			{
				fprintf(stderr, "Error: Ungueltige Zeichen, oder negative Zahlen vorhande.");
				free(c);
				free(g);
				free(g_m);
				return EXIT_FAILURE;
			}

			if ((fir == 1) && (no == 1) && (temp != 32) && (temp != 10) && (temp < 48 || temp > 57)) /*g_m wird verarbeitet. Die erste Stelle wurde bereits gespeichert. */
			{
				g_m[k] = g_m[k] *1000;
				g_m[k] = inlineAddition(g_m[k], temp);
			}
			else if ((fir == 1) && (no == 1) && (temp != 32) && (temp != 10) && (temp > 47) && (temp < 58)) /*g wird verarbeitet. Die erste Stelle wurde bereits gespeichert.*/
			{
				g[k] = g[k] *10;
				tomp = inlineSubtraction(temp, ac);
				g[k] = inlineAddition(g[k], tomp);
			}

			if ((fir == 0) && (no == 1) && (temp < 48 || temp > 57)) /*Erste Stelle g_m */
			{
				g_m[k] = temp;
				g[k] = 0;
				fir = 1;
			}
			else if ((fir == 0) && (no == 1) && (temp > 47) && (temp < 58)) /*Erste Stelle g */
			{
				g_m[k] = 0;

				g[k] = inlineSubtraction(temp, ac);
				fir = 1;
			}

			if ((temp == 32) && (no == 1))
			{

				if (g_m[k] == 102102 || g_m[k] == 98102 || g_m[k] == 97119102 || g_m[k] == 110102 || g_m[k] == 0)
				{
					k++;
					fir = 0;
				}
				else
				{
					fprintf(stderr, "Error: Ungueltige Zeichen, oder negative Zahlen vorhande.");
					free(c);
					free(g);
					free(g_m);
					return EXIT_FAILURE;
				}
			}

			if (temp == 10) /*nächste Zeile*/
			{
				no++;
				fir = 0;
			}
		}
		fclose(fp1);
	}
	k++;

	int *v = (int*) malloc(n *(sizeof(*v)));
	int *y = (int*) malloc(n *(sizeof(*y)));
	int *y2 = (int*) malloc(k *(sizeof(*y2)));

	for (i = 0; i < n; i++)	//Standart: Empty Container
	{
		y[i] = -1;
	}

	for (i = 0; i < k; i++)	//Standart: Empty Box
	{
		y2[i] = -1;
	}

	int blanc = 102102; /*standart ist First Fit, falls  kein Fit-Befehl angeben wurde */

	for (f = 0; f < k; f++)
	{

		if (g_m[f] == 102102)
		{
			blanc = 102102;
		} /*First Fit*/
		else if (g_m[f] == 98102)
		{
			blanc = 98102;
		} /*Best Fit*/
		else if (g_m[f] == 97119102)
		{
			blanc = 97119102;
		} /*AWF*/
		else if (g_m[f] == 110102)
		{
			blanc = 110102;
		} /*Next Fit*/
		else
		{
			blanc = blanc;
		}

		if (g_m[f] == 98102 || blanc == 97119102 || blanc == 110102)
		{
			for (i = 0; i < n; i++)
			{
				v[i] = c[i];
			}
			qsort(v, n, sizeof(int), cmpfunc);
		}

		if ((blanc == 102102) && (g[f] != 0))
		{
			i = 0;
			while ((y2[f] == -1) && (g[f] != 0))
			{

				if ((i == n - 1) && (c[n - 1] < g[f]))
				{
					fprintf(stdout, "validation failed");
					free(c);
					free(y);
					free(g);
					free(g_m);
					free(v);
					free(y2);
					return EXIT_FAILURE;
				}

				if (c[i] >= g[f])
				{

					y2[f] = i;
					y[i] = -2;
					c[i] = inlineSubtraction(c[i], g[f]);
					nxtf = i;
				}
				i++;
			}
		}
		else if ((blanc == 98102) && (g[f] != 0))
		{
			i = 0;
			while (y2[f] == -1)
			{

				if ((i == n - 1) && (v[i] < g[f]))
				{
					fprintf(stdout, "validation failed");
					free(c);
					free(y);
					free(g);
					free(g_m);
					free(v);
					free(y2);
					return EXIT_FAILURE;
				}

				if (v[i] >= g[f])
				{
					j = 0;
					while (y2[f] == -1)
					{

						if (v[i] == c[j])
						{
							y2[f] = j;
							y[j] = -2;
							c[j] = inlineSubtraction(c[j], g[f]);
							v[i] = inlineSubtraction(v[i], g[f]);

							for (s = i; s > 0; s--)
							{

								if (v[s] < v[s - 1])
								{
									temp = v[s];
									v[s] = v[s - 1];
									v[s - 1] = temp;
								}
							}

							nxtf = j;
						}

						j++;
					}
				}
				i++;
			}
		}
		else if ((blanc == 97119102) && (g[f] != 0))
		{

			if (v[n - 1] < g[f])
			{
				fprintf(stdout, "validation failed");
				free(c);
				free(y);
				free(g);
				free(g_m);
				free(v);
				free(y2);
				return EXIT_FAILURE;
			}

			if (g[f] <= v[n - 2])
			{
				i = 0;
				while ((y2[f] == -1) && (g[f] != 0))
				{
					if (c[i] == v[n - 2])
					{
						y2[f] = i;
						y[i] = -2;
						c[i] = inlineSubtraction(c[i], g[f]);
						nxtf = i;
					}
					i++;
				}
			}
			else if (g[f] <= v[n - 1])
			{
				i = 0;
				while ((y2[f] == -1) && (g[f] != 0))
				{

					if (c[i] == v[n - 1])
					{
						y2[f] = i;
						y[i] = -2;
						c[i] = inlineSubtraction(c[i], g[f]);
						nxtf = i;
					}
					i++;
				}
			}
		}
		else if ((blanc == 110102) && (g[f] != 0))
		{

			if (v[n - 1] < g[f])
			{
				fprintf(stdout, "validation failed");
				free(c);
				free(y);
				free(g);
				free(g_m);
				free(v);
				free(y2);
				return EXIT_FAILURE;
			}

			if (c[nxtf] >= g[f])

			{

				y2[f] = nxtf;
				y[nxtf] = -2;

				c[nxtf] = inlineSubtraction(c[nxtf], g[f]);
				nxtf = nxtf;
			}
			else
			{

				while (y2[f] == -1)
				{

					nxtf = (nxtf + 1) % (n);

					if (c[nxtf] >= g[f])
					{
						y2[f] = nxtf;
						y[nxtf] = -2;
						c[nxtf] = inlineSubtraction(c[nxtf], g[f]);
					}
				}
			}
			/*
			 */

		}
	}

	FILE * file;
	file = fopen(argv[2], "w");
	for (i = 0; i < n; i++)
	{
		fprintf(file, "%d: ", i);

		if (y[i] == -2)
		{
			for (j = 0; j < k; j++)
			{
				if (y2[j] == i)
				{
					fprintf(file, " %d", g[j]);
				}
			}
		}
		else if (y[i] == -1)
		{
			fprintf(file, " 0");
		}
		fprintf(file, "\n");
	}

	fclose(file);

	free(c);
	free(g_m);
	free(y);
	free(y2);
	free(g);
	free(v);

	return EXIT_SUCCESS;
}
