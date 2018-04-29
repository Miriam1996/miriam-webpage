/**
 * @author Miriam Schnoll
 * Cs381/31 Project 3
 */
import java.io.PrintWriter;
import java.util.Scanner;

public class EightConnectCC {
	private int numRows;
	private int numCols;
	private int minVal;
	private int maxVal;
	private int newMin;
	private int newMax;
	private int newLabel;
	private int[] EQAry;
	private int[][] zeroFramedAry;
	private int[] NeighborAry;
	// holds property values
	Property[] property;

	public EightConnectCC(int r, int c, int minV, int maxV) {
		numRows = r;
		numCols = c;
		minVal = minV;
		newMin = minVal;
		maxVal = maxV;
		newMax = maxVal;
		zeroFramedAry = new int[numRows + 2][numCols + 2];
		NeighborAry = new int[5];
		property = new Property[(numRows * numCols) / 2 + 1];
		EQAry = new int[(numRows * numCols) / 2 + 1];
		for (int i = 0; i < (numRows * numCols) / 2 + 1; i++) {
			EQAry[i] = i;
		}
		for (int i = 0; i < (numRows * numCols) / 2 + 1; i++) {
			Property p = new Property(i);
			property[i] = p;
		}
	}

	private void loadImage(Scanner in) {
		String t = "";
		for (int i = 1; i < numRows + 1; i++) {
			for (int j = 1; j < numCols + 1; j++) {
				if (in.hasNext())
					t = in.next();
				zeroFramedAry[i][j] = Integer.parseInt(t);

			}

		}

	}

	private void zeroFrame() {
		for (int i = 0; i < numRows + 2; i++) {
			zeroFramedAry[i][0] = 0;
			zeroFramedAry[i][numCols + 1] = 0;
		}
		for (int j = 0; j < numCols + 2; j++) {
			zeroFramedAry[0][j] = 0;
			zeroFramedAry[numRows + 1][j] = 0;
		}
	}

	private void loadNeighbors(int i, int j, int pass) {
		// 1st and 3rd pass top3 and left
		int f = j - 1;
		if (pass == 1 || pass == 3) {
			for (int t = 0; t < 5; t++) {
				if (t < 3)
					NeighborAry[t] = zeroFramedAry[i - 1][f];
				else if (t == 3)
					NeighborAry[t] = zeroFramedAry[i][j - 1];
				else
					NeighborAry[t] = zeroFramedAry[i][j];
				f++;

			}
		} // 2nd pass bottom3 and right
		else {
			for (int t = 0; t < 5; t++) {
				f = j + 1;
				if (t < 3)
					NeighborAry[t] = zeroFramedAry[i + 1][f];

				else if (t == 3)
					NeighborAry[t] = zeroFramedAry[i][j + 1];
				else
					NeighborAry[t] = zeroFramedAry[i][j];
				f--;
			}

		}
	}

	// check if all neigbors are zeros
	private boolean allZero() {
		for (int t = 0; t < 4; t++) {
			if (NeighborAry[t] != 0)
				return false;
		}
		return true;

	}

	// checks if all neighbors have same label
	private boolean sameLabel() {
		for (int t = 0; t < 3; t++) {
			// not equal or not equal to 0
			if (NeighborAry[t] != NeighborAry[t + 1] && NeighborAry[t] != 0
					|| NeighborAry[t] != NeighborAry[t + 1] && NeighborAry[t + 1] != 0)
				return false;
		}
		return true;
	}

	// gets lowest non zero label
	private int minLabel() {
		int i = 0;
		while (NeighborAry[i] == 0)
			i++;
		int min = NeighborAry[i];
		for (int t = 0; t < 4; t++)
			if (NeighborAry[t] < min && NeighborAry[t] != 0)
				min = NeighborAry[t];

		return min;
	}

	private void EightConnectCC_Pass1() {
		for (int i = 1; i < numRows + 1; i++) {
			for (int j = 1; j < numCols + 1; j++) {
				if (zeroFramedAry[i][j] > 0) {
					loadNeighbors(i, j, 1);
					/*
					 * if all neigbors are zero then newlabel++ set the
					 * NeighborAry[i][j] to newLabel
					 */
					if (allZero()) {
						newLabel++;
						zeroFramedAry[i][j] = newLabel;
					} /*
						 * if all neighbors have the same label update to
						 * NeighborAry[t] needs to check if some labels are zero
						 */
					else if (sameLabel() && !allZero()) {
						int p = 0;
						while (NeighborAry[p] == 0)
							p++;
						zeroFramedAry[i][j] = NeighborAry[p];
					} else if (!sameLabel() && !allZero()) {

						zeroFramedAry[i][j] = minLabel();
						updateEQAry();
					}
				}
			}
		}
	}

	// fix updateEQAry()
	private void updateEQAry() {
		for (int k = 0; k < 4; k++) {
			if (NeighborAry[k] != 0)
				EQAry[NeighborAry[k]] = minLabel();
		}
	}

	private void EightConnectCC_Pass2() {
		for (int i = numRows + 1; i > 0; i--) {
			for (int j = numCols + 1; j > 0; j--) {
				if (zeroFramedAry[i][j] > 0) {
					loadNeighbors(i, j, 2);
					if (!sameLabel() && !allZero()) {
						zeroFramedAry[i][j] = minLabel();
						updateEQAry();
					}
				}

			}
		}

	}

	private void EightConnectCC_Pass3() {
		for (int i = 1; i < numRows + 1; i++) {
			for (int j = 0; j < numCols + 1; j++) {
				if (zeroFramedAry[i][j] > 0) {
					zeroFramedAry[i][j] = EQAry[zeroFramedAry[i][j]];
					// keep track of number of pixels per label
					property[zeroFramedAry[i][j]].numbpixels++;
					// gets minRow for first time
					if (property[zeroFramedAry[i][j]].minRow == -1)
						property[zeroFramedAry[i][j]].minRow = i;
					/*
					 * check if current row i is less than min row in order to
					 * get property rectangular box of pixels
					 */
					else if (i < property[zeroFramedAry[i][j]].minRow)
						property[zeroFramedAry[i][j]].minRow = i;
					// gets minCol for first time
					if (property[zeroFramedAry[i][j]].minCol == -1)
						property[zeroFramedAry[i][j]].minCol = j;
					else if (i < property[zeroFramedAry[i][j]].minCol)
						property[zeroFramedAry[i][j]].minCol = j;
					if (property[zeroFramedAry[i][j]].maxRow == -1)
						property[zeroFramedAry[i][j]].maxRow = i;
					else if (i > property[zeroFramedAry[i][j]].maxRow)
						property[zeroFramedAry[i][j]].maxRow = i;
					if (property[zeroFramedAry[i][j]].maxCol == -1)
						property[zeroFramedAry[i][j]].maxCol = j;
					else if (i > property[zeroFramedAry[i][j]].maxCol)
						property[zeroFramedAry[i][j]].maxCol = j;

				}
			}
		}
	}

	private void manageEQAry() {
		int count = 0;
		for (int i = 1; i <= newLabel; i++) {
			if (EQAry[i] == i) {
				count++;
				EQAry[i] = count;
			} else
				EQAry[i] = EQAry[EQAry[i]];
		}
		// gets actual number of labels
		newMax = count;
	}

	private void prettyPrint(PrintWriter p, int pass) {
		p.println("Pass " + pass);
		for (int i = 1; i < numRows + 1; i++) {
			for (int j = 1; j < numCols + 1; j++) {
				if (zeroFramedAry[i][j] != 0)
					p.print(zeroFramedAry[i][j] + " ");
				else
					p.print("  ");
			}
			p.println();
		}
	}

	private void printEQ(PrintWriter p) {
		p.println("EQ Table");
		for (int k = 1; k <= newLabel; k++) {
			p.print(EQAry[k] + " ");
		}
		p.println();

	}

	private void printPass3(PrintWriter p2) {
		p2.println(numRows + " " + numCols + " " + newMin + " " + newMax);
		for (int i = 1; i < numRows + 1; i++) {
			for (int j = 1; j < numCols + 1; j++) {
				p2.print(zeroFramedAry[i][j] + " ");
			}
			p2.println();
		}

	}

	private void printCCProperty(PrintWriter p3) {
		p3.println(numRows + " " + numCols + " " + newMin + " " + newMax);
		p3.println(newMax);
		for (int i = 1; i <= newMax; i++) {
			p3.println(property[i].label);
			p3.println(property[i].numbpixels);
			p3.println(property[i].minRow - 1 + " " + (property[i].minCol - 1));
			p3.println(property[i].maxRow - 1 + " " + (property[i].maxCol - 1));
		}
	}

	public void EightConnect(Scanner in, PrintWriter p1, PrintWriter p2, PrintWriter p3) {
		loadImage(in);
		zeroFrame();
		EightConnectCC_Pass1();
		prettyPrint(p1, 1);
		printEQ(p1);
		EightConnectCC_Pass2();
		prettyPrint(p1, 2);
		printEQ(p1);
		manageEQAry();
		printEQ(p1);
		EightConnectCC_Pass3();
		prettyPrint(p1, 3);
		printPass3(p2);
		printEQ(p1);
		printCCProperty(p3);
	}
}
