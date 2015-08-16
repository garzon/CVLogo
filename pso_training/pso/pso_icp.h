#ifndef PSO_ICP_H
#define PSO_ICP_H

#include <vector>

#include <opencv2/opencv.hpp>

#include "particle.h"

template <typename ParamsType>
class PSO_ICP
{
    bool reInit_flag;
    const int particle_num,generation,kmeans_generation,kmeans_k;
    std::pair<double, cv::Mat> *swarm_best_position;
    cv::Mat last_best_position;
	std::vector<Particle<ParamsType>> particles;
    int *swarm_id_of_particles;
    double best_cost;
    cv::Mat *kmeans_centroid;

    void kmeans();
        void kmeans_set_centroid();
        void kmeans_set_swarm_id();
        void kmeans_update_centroid();

	cv::Mat _solve();

public:

	PSO_ICP(ICostFunction<ParamsType>*);

	ParamsType solve();

    ~PSO_ICP();
};

template <typename ParamsType>
PSO_ICP<ParamsType>::PSO_ICP(ICostFunction<ParamsType> *costFunc) :
	particle_num(32),
	kmeans_k(3),
	kmeans_generation(10),
	generation(20)
{
	reInit_flag = false;
	for (int i = 0; i<particle_num; i++)
		particles.emplace_back(costFunc);
	swarm_best_position = new std::pair<double, cv::Mat>[kmeans_k];
	kmeans_centroid = new cv::Mat[kmeans_k];
	swarm_id_of_particles = new int[particle_num];
}

template <typename ParamsType>
PSO_ICP<ParamsType>::~PSO_ICP() {
	delete[] swarm_best_position;
	delete[] swarm_id_of_particles;
	delete[] kmeans_centroid;
}

template <typename ParamsType>
void PSO_ICP<ParamsType>::kmeans_set_swarm_id(){
	for (int j = 0; j<particle_num; j++){
		double dist = COST_INF;
		for (int i = 0; i<kmeans_k; i++){
			cv::Mat diff = particles[j].position - kmeans_centroid[i];
			double tmp = diff.dot(diff);
			if (tmp<dist){
				dist = tmp;
				swarm_id_of_particles[j] = i;
			}
		}
	}
}

template <typename ParamsType>
void PSO_ICP<ParamsType>::kmeans_update_centroid(){
	cv::Mat *new_kmeans_centroid = new cv::Mat[kmeans_k];
	int *counter = new int[kmeans_k];
	for (int i = 0; i<kmeans_k; ++i){
		counter[i] = 0;
		new_kmeans_centroid[i] = cv::Mat(ParamsType::dimension_of_freedom, 1, CV_64F, cv::Scalar::all(0));
	}
	for (int j = 0; j<particle_num; j++){
		counter[swarm_id_of_particles[j]]++;
		new_kmeans_centroid[swarm_id_of_particles[j]] = new_kmeans_centroid[swarm_id_of_particles[j]] + particles[j].position;
	}
	for (int i = 0; i<kmeans_k; ++i){
		if (counter[i] != 0)
			new_kmeans_centroid[i] = new_kmeans_centroid[i] / (1.0*counter[i]);
	}
	delete[] kmeans_centroid;
	kmeans_centroid = new_kmeans_centroid;
	delete[] counter;
}

template <typename ParamsType>
void PSO_ICP<ParamsType>::kmeans_set_centroid(){
	int *p = new int[particle_num];
	for (int i = 0; i<particle_num; i++)
		p[i] = i;
	for (int i = 0; i<kmeans_k; i++){
		int pick = rand() % (particle_num - i);
		kmeans_centroid[i] = particles[p[pick]].position;
		p[pick] = p[particle_num - i - 1];
	}
	delete[] p;
}

template <typename ParamsType>
void PSO_ICP<ParamsType>::kmeans(){
	kmeans_set_centroid();
	for (int i = 0; i<kmeans_generation; i++){
		kmeans_set_swarm_id();
		if (i != kmeans_generation - 1)
			kmeans_update_centroid();
	}
}

template <typename ParamsType>
cv::Mat PSO_ICP<ParamsType>::_solve() {

	if (reInit_flag){
		for (int i = 0; i<particle_num; i++)
			particles[i].reInit(last_best_position);
	} else {
		reInit_flag = true;
	}

	for (int j = 0; j<particle_num; j++){
		particles[j].calcCost();
	}

	for (int j = 0; j<kmeans_k; j++){
		swarm_best_position[j].first = COST_INF;
	}

	for (int i = 0; i<generation; i++){

		kmeans();

		// find the best particle in each swarm/cluster
		for (int j = 0; j < particle_num; j++) {
			double &best_cost = swarm_best_position[swarm_id_of_particles[j]].first;
			if (best_cost > particles[j].cost) {
				best_cost = particles[j].cost;
				swarm_best_position[swarm_id_of_particles[j]].second = particles[j].position.clone();
			}
		}

		// update the stat of particles
		for (int j = 0; j < particle_num; j++) {
			cv::Mat &swarm_global_best_position = swarm_best_position[swarm_id_of_particles[j]].second;
			particles[j].update(swarm_global_best_position);
		}

	}

	// find the real global best particle in history

	best_cost = COST_INF;
	for (int j = 0; j<kmeans_k; j++) {
		if (swarm_best_position[j].first < best_cost) {
			best_cost = swarm_best_position[j].first;
			last_best_position = swarm_best_position[j].second.clone();
		}
	}

	return last_best_position;
}

template <typename ParamsType>
ParamsType PSO_ICP<ParamsType>::solve() {
	return ParamsType(_solve());
}

#endif // PSO_ICP_H
