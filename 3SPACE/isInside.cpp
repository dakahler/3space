int isInside(double x,double y)
{
	int numint=0;
	double camslope=(y-200)/(x-200),xsol;
	LineEq *trav_l=first_l->next;

	while (trav_l!=NULL) {
		xsol=((camslope*x)-(y)-(trav_l->m*trav_l->p2x)+(trav_l->p2y))/
			  (camslope-trav_l->m);

		if (trav_l->p1x>trav_l->p2x)
			if ((xsol>trav_l->p2x)&&(xsol<trav_l->p1x))
				numint++;
		if (trav_l->p2x>trav_l->p1x)
			if ((xsol>trav_l->p1x)&&(xsol<trav_l->p2x))
				numint++;
		if (trav_l->p2x==trav_l->p1x)
			if (xsol>(trav_l->p1x-1) || xsol<(trav_l->p1x+1))
				numint++;
		printf("numint: %d\n",numint);

		trav_l=trav_l->next;
	}
	if (numint%2==0)
		return 0;
	else return 1;
}
