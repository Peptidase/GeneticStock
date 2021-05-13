#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>

//This code was copied/Cloned from a good peice I saw on Geeks for geeks on a simple genetic algorithm

using namespace std;

//We can initialize the total amount of genes and the pool we can select from in possibilities.
const string genes = "abcdefghijklmnopqrstuvwxyz ";


//We define out goal/target that we can measure the fitness from.
const string target = "arif is the coolest guy";


#define POPULATION_SIZE 100 // define directive that essentially is a global variable but treated as a "macro value" that is replaced in 
//All occurances in the code via compiler.

int randomNum(int start,int end){
    int range = (end-start)+1;
    int random = start + (rand()%range); // Rand() will return a integral number between 0 and MAX, 
    //THis line will ensure it returns between the values specified in the range.
    return random;
}

char mutated_genes(){ //This will return the mutated gene outcome when we need to mutate a specific gene.
    int len = genes.size();
    int r = randomNum(0,len-1);
    return genes[r];
}

string create_gnome(){ //Generates a random starting gnome for the initial population
    int len = target.size();
    string gnome = "";

    for(int i = 0; i<len; i++){
        gnome+=mutated_genes();
    }
    return gnome;

}


class Individual{
    public:
    string chromosome;
    int fittness;
    Individual(string chromosome);
    Individual(const Individual &I); // Copy constructor    
    Individual mate(Individual parent2);
    int cal_fittness();
};



Individual::Individual(string chromosome)
{
    this->chromosome = chromosome;
    fittness = cal_fittness();
}

Individual::Individual(const Individual &I){
    this->chromosome = I.chromosome;
    this->fittness = cal_fittness();
}


int Individual::cal_fittness(){ // FOr some reason the code uses a higher fittness == worse. //Works

    int fittness = 0;
    int len = target.size();    
    for(int i = 0; i < len; i++){
        if(chromosome[i] != target[i]){
            fittness++;
        }
    }
    return fittness;
}

//TODO Implement the mating, and the overall iterative generation process of storing population, picking best and mating.
//Then we take away 2 worst "individuals" and replace with 2 new children.


Individual Individual::mate(Individual par2)
{
    string child_chromosome = "";

    int len = chromosome.size();

    for(int i = 0; i < len; i++){
        //random probability
        float p = randomNum(0,100)/100;
        if(p < 0.45)
        {
            child_chromosome+=chromosome[i];
        }
        else if(p < 0.90){
            child_chromosome+=par2.chromosome[i];
        }
        else{
            child_chromosome+=mutated_genes();
        }
    }

    return Individual(child_chromosome);
}

bool operator<(const Individual &i1, const Individual &i2) //TO make the objects individuals sortable by the algorithm "sort"
{
    return i1.fittness < i2.fittness;

}

//Generation Code
int main()
{   
    srand((unsigned)(time(0)));
    int generation = 0;

    std::vector<Individual> population;
    bool found = false;

    for(int i = 0; i < POPULATION_SIZE; i++)
    {
        string genome = create_gnome();
        population.push_back(Individual(genome));
    }


    while(!found)
    {
        sort(population.begin(),population.end()); //We want to sort in terms of fitness.

        if(population[0].fittness <= 0){ // Could improve this 
            found = true;
            break;
        }

        std::vector<Individual> new_generation;

        //ELitism, as started on the tutorial it takes 10% best performing candidates that goto the next generation.

        int s = (10*POPULATION_SIZE) / 100;
        for(int i = 0; i<s; i++){
            new_generation.push_back(population[i]);

        }
        
        //The 50% of the fittest pop will mate.

        s = (90*POPULATION_SIZE) / 100;
        for(int i = 0; i<s; i++)
        { 
            int len = population.size();
            int r = randomNum(0,50);
            Individual parent1 = population[r];
            r = randomNum(0,50);
            Individual parent2 = population[r];
            Individual offspring = parent1.mate(parent1);
            new_generation.push_back(offspring);        
        }
    
        population = new_generation; 
        std::cout<<"GENERATING !"<<std::endl;
        std::cout<<"Generation: "<<generation<<std::endl;
        std::cout<<"String: "<<population[0].chromosome<<std::endl;
        std::cout<<"Fittness: "<<population[0].fittness<<std::endl;

    
        cin.get();
        generation++;
    }

    std::cout<<"Generation: "<<generation<<std::endl;
    std::cout<<"String: "<<population[0].chromosome<<std::endl;
    std::cout<<"Fittness: "<<population[0].fittness<<std::endl;

    return 0;
};


