

public class Determinante{

     public static int det(int[][] A){
		int a =-1;
		int g = 0;

		int b = 0;
		int c = 0;





	/**************/
		if(A.length>2){	
			int R = A.length-1;
			int B[][] = new int[R][R];

			for(int i = 0;i<R+1;i++){

				for(int j=0;j<R+1;j++){
				for(int k=0;k<R+1;k++){	
				if(j!=0&&k!=i&&b<R){
				B[b][c]=A[j][k];				
				c++; if(c==R){c=0; b++;}
						}
				}}
				b = 0; c = 0;
				a += Math.pow(-1,i)*A[0][i]*det(B);

			}	
			a +=1;
		}
			
		if(A.length==2){
		a = A[0][0]*A[1][1]-A[0][1]*A[1][0];
		}
	
		if(A.length==1){
		a = A[0][0];
		}		
		return a;
	 } 
	


  //Testaufrufe
  public static void main(String[] args) {
    int[][] Feld1 = {{5}};
    if (det(Feld1) != 5) {
      System.out.println("Test 1 fehlergeschlagen.");
			      System.out.println(det(Feld1));
    } else {
      System.out.println("Test 1 bestanden.");
    } 

    int[][] Feld2 = {{3,2},{1,1}};
    if (det(Feld2) != 1) {
      System.out.println("Test 2 fehlergeschlagen.");
		      System.out.println(det(Feld2));
    } else {
      System.out.println("Test 2 bestanden.");
    }

    int[][] Feld3 = {{1,2,3},{6,5,4},{7,8,9}};
    if (det(Feld3) != 0) {
      System.out.println("Test 3 fehlergeschlagen.");
	      System.out.println(det(Feld3));
    } else {
      System.out.println("Test 3 bestanden.");
    }

    int[][] Feld4 = {{0,1,2},{3,2,1},{1,1,0}};
    if (det(Feld4) != 3) {  
      System.out.println("Test 4 fehlergeschlagen.");
		      System.out.println(det(Feld4));
    } else {
      System.out.println("Test 4 bestanden.");
    }

	    int[][] Feld5 = {{0,1,2,2},{3,2,1,2},{1,1,0,2},{3,2,1,1}};
    if (det(Feld5) != -3) {  
      System.out.println("Test 5 fehlergeschlagen.");
	      System.out.println(det(Feld5));
    } else {
      System.out.println("Test 5 bestanden.");
		
    }

		    int[][] Feld6 = {{7,23,1,5},{7,3,1,234},{1,1,0,2},{3,2,1,1}};
    if (det(Feld6) != -3813) {  
      System.out.println("Test 6 fehlergeschlagen.");
	      System.out.println(det(Feld6));
    } else {
      System.out.println("Test 6 bestanden.");

		
    }


		    int[][] Feld7 = {{7,23,1,5,32},{7,3,1,234,34},{1,341,0,2,87},{23,23,21,1,5},{23,2,21,1,6}};
    if (det(Feld7) != 58246417) {  
      System.out.println("Test 7 fehlergeschlagen.");
	      System.out.println(det(Feld7));
    } else {
      System.out.println("Test 7 bestanden.");

		
    }



  }
}
