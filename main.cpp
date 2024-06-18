
#include <iostream>
#include <fstream>
#include <chrono>
#include "List/GraphList.h"
#include "Matrix/GraphIncidence.h"
#include "Utils/utils.h"
#include "Algorithms/Prim/Prim.h"
#include "Algorithms/Bellman/Bellman.h"
#include "Algorithms/Dijkstra/Dijkstra.h"
#include "Algorithms/Kruskal/Kruskal.h"
void menu();
void test();
void showMainMenu();
void showMSTMenu();
void showSPMenu();
void handleMSTMenu(GraphList& graphList, GraphIncidence& graphIncidence, GraphList& graphListSP, GraphIncidence& graphIncidenceSP);
void handleSPMenu(GraphList& graphList, GraphIncidence& graphIncidence);
//asd
template <typename Func>
double measureTime(Func func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    return duration.count();
}


int main() {
    std::setlocale(LC_ALL, "Polish");


    int wybor, dEdges=0, UDEdges=0, nm=0;

    do{
        printf("Choose enviroment:\n1. Menu\n\n");
        std::cin >> wybor;
        if(wybor == 1)menu();
    //    else if(wybor == 2)test();
     //   else if(wybor ==3 )break;
    }while(wybor != 1);
    if(wybor==1)menu();
 //   else if(wybor==2)test();


    return 0;
}





void menu() {
    GraphIncidence matrixGraphMST(0, 0);
    GraphIncidence matrixGraphSP(0, 0);
    GraphList listGraphMST(0);
    GraphList listGraphSP(0);

    while (true) {
        showMainMenu();

        int choice;
        std::cin >> choice;

        if (choice == 0) {
            std::cout << "Exiting...\n";
            break;
        }

        switch (choice) {
            case 1: {
                std::string filename;
                std::cout << "Enter filename: ";
                std::cin >> filename;
                loadGraphFromFile(filename, listGraphSP, matrixGraphSP, listGraphMST, matrixGraphMST);
                break;
            }

            case 2: {
                handleMSTMenu(listGraphMST, matrixGraphMST, listGraphSP, matrixGraphSP);
                break;
            }
            case 3: {
                handleSPMenu(listGraphSP, matrixGraphSP);
                break;
            }
            default: {
                std::cout << "Invalid choice. Please try again.\n";
                break;
            }
        }
    }
}

void showMainMenu() {
    std::cout << "\nMenu:\n";
    std::cout << "1. Load graph from file\n";

 //   std::cout << "2. Display graph\n";
    std::cout << "2. Run MST algorithms\n";
    std::cout << "3. Run shortest path algorithms\n";
    std::cout << "0. Exit\n";
    std::cout << "Enter your choice: ";
}

void showMSTMenu() {
    std::cout << "\nMST Algorithms Menu:\n";
    std::cout << "1. Generate Graph\n";
    std::cout << "2. Show Graph\n";
    std::cout << "3. Prim's Algorithm\n";
    std::cout << "4. Kruskal's Algorithm\n";
    std::cout << "0. Back to Main Menu\n";
    std::cout << "Enter your choice: ";
}

void showSPMenu() {
    std::cout << "\nSP Algorithms Menu:\n";
    std::cout << "1. Generate Graph\n";
    std::cout << "2. Show Graph\n";
    std::cout << "3. Dijkstra's Algorithm\n";
    std::cout << "4. Bellman-Ford Algorithm\n";
    std::cout << "0. Back to Main Menu\n";
    std::cout << "Enter your choice: ";
}

void handleMSTMenu(GraphList& graphListMST, GraphIncidence& graphIncidenceMST, GraphList& graphListSP, GraphIncidence& graphIncidenceSP) {
    int choice;
    do {
        showMSTMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                int num_vertices;
                double density;
                std::cout << " Enter number of vertices: ";
                std::cin >> num_vertices;
                std::cout << " Enter density (0-1): ";
                std::cin >> density;
                generateGraph(graphIncidenceSP, graphListSP, graphIncidenceMST, graphListMST, num_vertices, density);
                break;
            case 2:
                displayGraph(graphListSP, graphIncidenceSP);
                break;
            case 3:
                std::cout << "\nRunning Prim's Algorithm...\n";
                primMST(graphIncidenceMST);
                primMST(graphListMST);
                break;
            case 4:
                std::cout << "\nRunning Kruskal's Algorithm...\n";
                //displayGraph(graphListMST, graphIncidenceMST);
                kruskalMST(graphIncidenceMST);
                kruskalMST(graphListMST);
                break;
            case 0:
                std::cout << "Returning to Main Menu...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

void handleSPMenu(GraphList& graphListSP, GraphIncidence& graphIncidenceSP) {
    int choice;
    do {
        showSPMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                int num_vertices;
                double density;
                std::cout << " Enter number of vertices: ";
                std::cin >> num_vertices;
                std::cout << " Enter density (0-1): ";
                std::cin >> density;
                generateGraph(graphIncidenceSP, graphListSP, num_vertices, density, true);
                break;
            case 2:
                displayGraph(graphListSP, graphIncidenceSP);
                break;
            case 3:
                std::cout << "\nRunning Dijkstra's Algorithm...\n";
                std::cout << "Enter source vertex: ";
                int source;
                std::cin >> source;
                printf("\nDijkstra for matrix\n");
                dijkstra(graphIncidenceSP, source);
                printf("\nDijkstra for list\n");
                dijkstra(graphListSP, source);
                break;
            case 4:
                std::cout << "\nRunning Bellman-Ford Algorithm...\n";
                std::cout << "Enter source vertex: ";
                std::cin >> source;
                printf("\nBellman-Ford for matrix\n");
                bellmanFord(graphIncidenceSP, source);
                printf("\nBellman-Ford for list\n");
                bellmanFord(graphListSP, source);
                break;
            case 0:
                std::cout << "Returning to Main Menu...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}








void test(){
    double dens[] = {0.25, 0.5, 0.99};
    //int vertexs[] = {10, 15,20, 25, 30, 35, 40, 45};
    int vertexs[] = {10000, 20000, 40000, 80000, 160000, 320000, 640000, 1280000};
    std::ofstream outputFile("output.txt");
    if(!outputFile.is_open()){
        std::cerr << "Could not open file";
        return;
    }

    double time;
    std::string name[4] = { "Prim", "Kruskal", "Dijkstra", "Bellman-Ford"};
    double sumTime[4][7][3][2] = {0};//algorytm, próby, gęstość, reprezentacja(lista/macierz)
    for (int i = 0; i <4; ++i) {
        for(int j = 0; j < 7; ++j) {
            for (int k = 0; k < 3; ++k) {
                for (int l = 0; l < 2; ++l) {

                    if(sumTime[i][j][k][l]!=0)printf("Aj, %d %d %d %d: %lf\n", i, j, k, l, sumTime[i][j][k][l]);
                    //sumTime[i][j][k][l]= i+j+k+l;
                }

            }
        }
    }
    int ma =50 ;

    for(int i = 0; i<3 ; i++) {//dla listy

        for (int j = 1; j < 8; j++) {
            std::cout << j << ", "<< i << std::endl;
            for(int m=0; m<ma; m++) {
               // std::cout << "m: "<<m << std::endl;

                GraphIncidence matrix(0, 0);
                GraphList list(0);
                generateGraph(matrix, list, j*25, dens[i], true);
                time = measureTime([&]() { primMST(matrix); });
                sumTime[0][j - 1][i][0] += time;
                time = measureTime([&]() { primMST(list); });
                sumTime[0][j - 1][i][1] += time;
                time = measureTime([&]() { kruskalMST(matrix); });
                sumTime[1][j - 1][i][0] += time;
                time = measureTime([&]() { kruskalMST(list); });
                sumTime[1][j - 1][i][1] += time;
                time = measureTime([&]() { dijkstra(matrix, 0); });
                sumTime[2][j - 1][i][0] += time;
                time = measureTime([&]() { dijkstra(list, 0); });
                sumTime[2][j - 1][i][1] += time;
                time = measureTime([&]() { bellmanFord(matrix, 0); });
                sumTime[3][j - 1][i][0] += time;
                time = measureTime([&]() { bellmanFord(list, 0); });
                sumTime[3][j - 1][i][1] += time;
            }


        }
        std::cout << "Density: " << dens[i] << std::endl;
        for(int j=0; j<2; j++){
            for(int k=0;k<4;k++){
                std::cout << name[k]<<std::endl;
                for(int l=0; l<7;l++){
                    printf("%lf\n", sumTime[k][l][i][j]/ma);
                }
                std::cout << std::endl;
            }
        }



    }


    std::string filename = "wyniki";
    std::string extension = ".csv";
    std::string fullFilename = filename;
    if (filename.size() < 4 || filename.substr(filename.size() - 4) != extension) {
        fullFilename += extension;
    }

    std::ofstream file(fullFilename);
    if (!file) {
        std::cerr << "Nie można otworzyć pliku " << fullFilename << std::endl;
        return;
    }
    std::string str="";
    file << "Rep;Dens;Trial\n" ;
    for (int trial = 0; trial < 7; ++trial) {
        for (int alg = 0; alg < 4; ++alg) {
            for (int rep = 0; rep < 2; ++rep) {
                for (int density = 0; density < 3; ++density) {

                    file << sumTime[alg][trial][density][rep]/ma << ";";
                }
            }
        }
        file << "\n";
    }




}