/**
 * @file evox_aleatory_5d.c
 * @version 12.0.0
 * @license GNU
 * @author Evolutia Technologies
 *
 * @title EVOX Aleatory 5D - Chaotic Autonomous Object Manifold Generation
 * @description Complete aleatory (stochastic) system for generating autonomous
 *              5D object manifolds with quantum-inspired probabilities,
 *              chaotic dynamics, and emergent behaviors
 */

/* ============================================================================
 * ANSI C89/90 Standard Headers
 * =========================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <time.h>
#include <stddef.h>
#include <errno.h>
#include <signal.h>
#include <stdarg.h>
#include <setjmp.h>
#include <float.h>
#include <limits.h>

/* POSIX Headers */
#ifdef __unix__
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#endif

#include <SDL2/SDL.h>

/* ============================================================================
 * Aleatory System Configuration
 * =========================================================================== */

#define PROGRAM_NAME         "EVOX Aleatory 5D"
#define PROGRAM_VERSION      "12.0.0"
#define PROGRAM_AUTHOR       "Evolutia"
#define PROGRAM_YEAR         "2026"

/* Advanced Object Generation */
#define MAX_OBJECTS          16              /* Reduced for stability */
#define MAX_OBJECT_TYPES     8               /* Different object types */
#define MANIFOLD_DIMS        5               /* 5D manifold: x,y,z,ψ,φ (quantum phases) */
#define MANIFOLD_RESOLUTION  8               /* Reduced resolution for performance */
#define MANIFOLD_POINTS      (MANIFOLD_RESOLUTION * MANIFOLD_RESOLUTION * MANIFOLD_RESOLUTION)

/* Chaotic Parameters */
#define CHAOS_DIMENSIONS     7               /* 7D chaos space */
#define LYAPUNOV_EXPONENTS   5               /* Number of Lyapunov exponents */
#define STRANGE_ATTRACTORS   4               /* Number of strange attractors */
#define BIFURCATION_POINTS   8               /* Bifurcation points */

/* Quantum-Inspired Parameters */
#define PROBABILITY_AMPLITUDES 5             /* Quantum probability amplitudes */
#define WAVE_FUNCTION_SIZE    64              /* Reduced wave function resolution */
#define ENTANGLEMENT_PAIRS    4               /* Max entangled object pairs */
#define DECOHERENCE_RATE      0.01f           /* Quantum decoherence rate */

/* Neural Network Architecture */
#define INPUT_NEURONS        24              /* Reduced for stability */
#define HIDDEN_NEURONS       32              /* Hidden layer neurons */
#define OUTPUT_NEURONS       16              /* Object control outputs */
#define QUANTUM_NEURONS      8               /* Quantum-inspired neurons */

/* Fuzzy Logic Systems */
#define FUZZY_INPUTS         12              /* Object perception inputs */
#define FUZZY_OUTPUTS        8               /* Object behavior outputs */
#define MEMBERSHIP_SETS      7               /* NB, NM, NS, ZE, PS, PM, PB */
#define RULE_BASE_SIZE       49

/* Aleatory Physics */
#define PLANCK_CONSTANT      6.626e-34f      /* Scaled for simulation */
#define SCHRODINGER_STEPS    50              /* Quantum evolution steps */
#define CHAOS_COUPLING       0.3f            /* Chaos-quantum coupling */
#define ZERO_POINT_ENERGY    0.5f            /* Zero-point energy */
#define GRAVITY_CONSTANT     9.81f           /* Gravity constant */
#define DAMPING_FACTOR       0.98f           /* Physics damping */
#define COLLISION_THRESHOLD  0.5f            /* Collision threshold */

/* Behavior States */
#define STATE_IDLE           0
#define STATE_MOVING         1
#define STATE_ROTATING       2
#define STATE_SCALING        3
#define STATE_INTERACTING    4
#define STATE_REPRODUCING    5
#define STATE_DYING          6

/* Rendering */
#define WINDOW_WIDTH         1280            /* Reduced for performance */
#define WINDOW_HEIGHT        960
#define QUANTUM_VISUALIZATION 1

/* ============================================================================
 * Basic Type Definitions
 * =========================================================================== */

typedef float vec5[5]; /* 5D vector: x, y, z, ψ (quantum phase), φ (probability amplitude) */
typedef float vec3[3]; /* 3D vector for rendering and environment */

/* ============================================================================
 * Basic Vector Operations
 * =========================================================================== */

/* 3D vector operations */
static void vec3_zero(vec3 v) {
	v[0] = 0.0f;
	v[1] = 0.0f;
	v[2] = 0.0f;
}

static void vec3_set(vec3 v, float x, float y, float z) {
	v[0] = x;
	v[1] = y;
	v[2] = z;
}

static void vec3_copy(vec3 dest, const vec3 src) {
	dest[0] = src[0];
	dest[1] = src[1];
	dest[2] = src[2];
}

static float vec3_length(const vec3 v) {
	return (float) sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

static void vec3_normalize(vec3 dest, const vec3 v) {
	float len = vec3_length(v);
	if (len > 1e-6f) {
		dest[0] = v[0] / len;
		dest[1] = v[1] / len;
		dest[2] = v[2] / len;
	} else {
		vec3_copy(dest, v);
	}
}

/* 5D vector operations */
static void vec5_zero(vec5 v) {
	v[0] = 0.0f;
	v[1] = 0.0f;
	v[2] = 0.0f;
	v[3] = 0.0f;
	v[4] = 0.0f;
}

static void vec5_set(vec5 v, float x, float y, float z, float psi, float phi) {
	v[0] = x;
	v[1] = y;
	v[2] = z;
	v[3] = psi;
	v[4] = phi;
}

static void vec5_copy(vec5 dest, const vec5 src) {
	dest[0] = src[0];
	dest[1] = src[1];
	dest[2] = src[2];
	dest[3] = src[3];
	dest[4] = src[4];
}

static void vec5_add(vec5 dest, const vec5 a, const vec5 b) {
	dest[0] = a[0] + b[0];
	dest[1] = a[1] + b[1];
	dest[2] = a[2] + b[2];
	dest[3] = a[3] + b[3];
	dest[4] = a[4] + b[4];
}

static void vec5_sub(vec5 dest, const vec5 a, const vec5 b) {
	dest[0] = a[0] - b[0];
	dest[1] = a[1] - b[1];
	dest[2] = a[2] - b[2];
	dest[3] = a[3] - b[3];
	dest[4] = a[4] - b[4];
}

static void vec5_mul_scalar(vec5 dest, const vec5 a, float s) {
	dest[0] = a[0] * s;
	dest[1] = a[1] * s;
	dest[2] = a[2] * s;
	dest[3] = a[3] * s;
	dest[4] = a[4] * s;
}

static float vec5_length(const vec5 v) {
	return (float) sqrt(
			v[0] * v[0] + v[1] * v[1] + v[2] * v[2] + v[3] * v[3] + v[4] * v[4]);
}

static void vec5_normalize(vec5 dest, const vec5 v) {
	float len = vec5_length(v);
	if (len > 1e-6f) {
		dest[0] = v[0] / len;
		dest[1] = v[1] / len;
		dest[2] = v[2] / len;
		dest[3] = v[3] / len;
		dest[4] = v[4] / len;
	} else {
		vec5_copy(dest, v);
	}
}

/* ============================================================================
 * Chaos State Vector (7D)
 * =========================================================================== */

typedef float chaos7[7];

typedef struct {
	chaos7 position;
	chaos7 velocity;
	float lyapunov_exponents[LYAPUNOV_EXPONENTS];
	float fractal_dimension;
	float kolmogorov_entropy;
	int attractor_type;
	float coupling_strength;
} ChaosState;

/* ============================================================================
 * Quantum Amplitude Structure
 * =========================================================================== */

typedef struct {
	float real; /* Real part of probability amplitude */
	float imag; /* Imaginary part of probability amplitude */
	float phase; /* Quantum phase */
	float probability; /* |ψ|² */
} QuantumAmplitude;

/* ============================================================================
 * Quantum State Structure
 * =========================================================================== */

typedef struct {
	QuantumAmplitude amplitudes[PROBABILITY_AMPLITUDES];
	float wave_function[WAVE_FUNCTION_SIZE];
	float hamiltonian[WAVE_FUNCTION_SIZE][WAVE_FUNCTION_SIZE];
	float eigenvalues[WAVE_FUNCTION_SIZE];
	float eigenvectors[WAVE_FUNCTION_SIZE][WAVE_FUNCTION_SIZE];
	int entangled_with[ENTANGLEMENT_PAIRS];
	float entanglement_strength[ENTANGLEMENT_PAIRS];
	float decoherence_time;
} QuantumState;

/* ============================================================================
 * Probability Distribution Structure
 * =========================================================================== */

typedef struct {
	float mean;
	float variance;
	float skewness;
	float kurtosis;
	float probability_cloud[100];
} ProbabilityDistribution;

/* ============================================================================
 * Aleatory Manifold Point
 * =========================================================================== */

typedef struct {
	vec5 position; /* x, y, z, ψ, φ */
	vec5 normal; /* 5D normal vector */
	vec5 quantum_velocity; /* Quantum evolution velocity */
	float curvature[5]; /* Principal curvatures */
	float mass; /* Point mass */
	float temperature; /* Point temperature */
	float energy; /* Point energy */
	float quantum_potential; /* Quantum potential Q = -ħ²/2m ∇²R/R */
	float probability_density; /* |ψ|² */
	ChaosState chaos; /* Chaotic dynamics at this point */
	QuantumAmplitude qamp; /* Quantum amplitude at this point */
} AleatoryManifoldPoint;

/* ============================================================================
 * Aleatory Object Manifold
 * =========================================================================== */

typedef struct {
	AleatoryManifoldPoint points[MANIFOLD_POINTS];
	int resolution;
	int total_points;
	float center_of_mass[5];
	float bounding_box[5][2];
	float volume;
	float surface_area;
	float total_quantum_entropy;
	float total_chaos_entropy;
	float wave_function_collapse_count;
} AleatoryManifold;

/* ============================================================================
 * Quantum Neural Network
 * =========================================================================== */

typedef struct {
	/* Quantum weights (complex numbers) */
	float weights_real[INPUT_NEURONS][HIDDEN_NEURONS];
	float weights_imag[INPUT_NEURONS][HIDDEN_NEURONS];
	float hidden_bias_real[HIDDEN_NEURONS];
	float hidden_bias_imag[HIDDEN_NEURONS];

	float output_weights_real[HIDDEN_NEURONS][OUTPUT_NEURONS];
	float output_weights_imag[HIDDEN_NEURONS][OUTPUT_NEURONS];
	float output_bias_real[OUTPUT_NEURONS];
	float output_bias_imag[OUTPUT_NEURONS];

	/* Quantum states */
	float hidden_amplitude[HIDDEN_NEURONS];
	float hidden_phase[HIDDEN_NEURONS];
	float output_amplitude[OUTPUT_NEURONS];
	float output_phase[OUTPUT_NEURONS];

	/* Quantum operators */
	float hamiltonian[INPUT_NEURONS][INPUT_NEURONS];
	float loss;
	float learning_rate;
	float quantum_temperature;
} QuantumNeuralNetwork;

/* ============================================================================
 * Aleatory Membership Structure
 * =========================================================================== */

typedef struct {
	float a, b, c, d; /* Trapezoidal parameters */
	ProbabilityDistribution dist; /* Probability distribution */
} AleatoryMembership;

/* ============================================================================
 * Aleatory Fuzzy Variable
 * =========================================================================== */

typedef struct {
	float min, max;
	AleatoryMembership sets[MEMBERSHIP_SETS];
	float crisp;
	float fuzzy[MEMBERSHIP_SETS];
	float probability[MEMBERSHIP_SETS];
} AleatoryFuzzyVariable;

/* ============================================================================
 * Aleatory Fuzzy Rule
 * =========================================================================== */

typedef struct {
	int antecedents[FUZZY_INPUTS];
	int consequent[FUZZY_OUTPUTS];
	float weight;
	float probability;
	float firing_distribution[100];
} AleatoryFuzzyRule;

/* ============================================================================
 * Aleatory Fuzzy System
 * =========================================================================== */

typedef struct {
	AleatoryFuzzyVariable inputs[FUZZY_INPUTS];
	AleatoryFuzzyVariable outputs[FUZZY_OUTPUTS];
	AleatoryFuzzyRule rules[RULE_BASE_SIZE];
	float rule_activations[RULE_BASE_SIZE];
	float aggregated[FUZZY_OUTPUTS][MEMBERSHIP_SETS];
	float probability_field[FUZZY_OUTPUTS][100];
} AleatoryFuzzySystem;

/* ============================================================================
 * Autonomous Aleatory Object
 * =========================================================================== */

typedef struct {
	int id;
	int type;
	int state;
	float age;
	float energy;
	float health;
	float mass;

	/* 5D Aleatory Manifold */
	AleatoryManifold manifold;

	/* Physics */
	vec5 position;
	vec5 velocity;
	vec5 acceleration;
	vec5 rotation;
	vec5 scale;
	vec5 goal;

	/* Quantum State */
	QuantumState quantum_state;
	float wave_function[WAVE_FUNCTION_SIZE];
	int entangled_partners[ENTANGLEMENT_PAIRS];
	float collapse_history[100];

	/* Chaos State */
	ChaosState chaos_state;
	float bifurcation_parameters[BIFURCATION_POINTS];

	/* Neural Networks */
	QuantumNeuralNetwork *quantum_brain;
	AleatoryFuzzySystem *aleatory_controller;

	/* Behavior Parameters with Probability Distributions */
	ProbabilityDistribution curiosity;
	ProbabilityDistribution fear;
	ProbabilityDistribution aggression;
	ProbabilityDistribution social_force;

	/* Relationships with Quantum Entanglement */
	int parent_id;
	int children[MAX_OBJECTS];
	int child_count;
	float quantum_affinity[MAX_OBJECTS]; /* Quantum entangled affinities */

	/* Rendering */
	vec3 render_position;
	float render_rotation[3][3];
	float quantum_glow;
} AleatoryObject;

/* ============================================================================
 * Aleatory Environment
 * =========================================================================== */

typedef struct {
	vec3 gravity;
	float time;
	float temperature;
	float pressure;
	float light_intensity;
	vec3 light_direction;
	float quantum_foam_density; /* Spacetime foam density */
	float vacuum_energy; /* Zero-point energy */
	float higgs_field; /* Higgs field strength */
} AleatoryEnvironment;

/* ============================================================================
 * Aleatory World
 * =========================================================================== */

typedef struct {
	AleatoryObject objects[MAX_OBJECTS];
	int object_count;
	AleatoryEnvironment env;
	float global_time;
	int generation;
	float mutation_rate;
	float selection_pressure;
	float quantum_decoherence_rate;
	float chaos_coupling;

	/* Global quantum field */
	float quantum_field[16][16][16]; /* Reduced size */
	float entanglement_matrix[MAX_OBJECTS][MAX_OBJECTS];
} AleatoryWorld;

/* ============================================================================
 * Forward Declarations
 * =========================================================================== */

static float quantum_random(void);
static float membership_trapezoid(float x, float a, float b, float c, float d);
static void update_object_physics(AleatoryObject *obj, float dt);
static void destroy_object(AleatoryWorld *world, int obj_idx);

/* ============================================================================
 * Utility Functions
 * =========================================================================== */

double get_time(void) {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (double) tv.tv_sec + (double) tv.tv_usec / 1000000.0;
}

void log_message(const char *fmt, ...) {
	va_list args;
	time_t now;
	char time_str[32];

	time(&now);
	strftime(time_str, sizeof(time_str), "%H:%M:%S", localtime(&now));

	printf("[%s] ", time_str);
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);
	printf("\n");
}

/* ============================================================================
 * Quantum Probability Functions
 * =========================================================================== */

static float quantum_random(void) {
	/* Quantum-inspired random number using wave function collapse */
	static float phase = 0.0f;
	phase = fmod(phase + 0.1f, 2.0f * 3.14159f);
	return 0.5f + 0.5f * sin(phase) * cos(phase * 1.618f);
}

static void quantum_amplitude_init(QuantumAmplitude *qa, float real, float imag) {
	qa->real = real;
	qa->imag = imag;
	qa->phase = atan2(imag, real);
	qa->probability = real * real + imag * imag;
}

/* ============================================================================
 * Strange Attractor Implementations
 * =========================================================================== */

static void lorenz_attractor(chaos7 state, float dt) {
	float x = state[0], y = state[1], z = state[2];
	float dx = 10.0f * (y - x); /* LORENZ_SIGMA */
	float dy = x * (28.0f - z) - y; /* LORENZ_RHO */
	float dz = x * y - (8.0f / 3.0f) * z; /* LORENZ_BETA */

	state[0] += dx * dt;
	state[1] += dy * dt;
	state[2] += dz * dt;

	/* Chaos dimensions */
	state[3] = sin(state[0] * 0.1f) * cos(state[1] * 0.1f);
	state[4] = cos(state[2] * 0.1f) * sin(state[0] * 0.1f);
	state[5] = state[3] * state[4];
	state[6] = (state[0] + state[1] + state[2]) * 0.1f;
}

static void roessler_attractor(chaos7 state, float dt) {
	float x = state[0], y = state[1], z = state[2];
	float dx = -y - z;
	float dy = x + 0.2f * y; /* ROESSLER_A */
	float dz = 0.2f + z * (x - 5.7f); /* ROESSLER_B, ROESSLER_C */

	state[0] += dx * dt;
	state[1] += dy * dt;
	state[2] += dz * dt;

	state[3] = sin(state[0] * 0.2f) * cos(state[1] * 0.2f);
	state[4] = sin(state[1] * 0.2f) * cos(state[2] * 0.2f);
	state[5] = sin(state[2] * 0.2f) * cos(state[0] * 0.2f);
	state[6] = (state[0] * state[0] + state[1] * state[1]) * 0.01f;
}

/* ============================================================================
 * Membership Function
 * =========================================================================== */

static float membership_trapezoid(float x, float a, float b, float c, float d) {
	if (x <= a || x >= d)
		return 0.0f;
	if (x >= b && x <= c)
		return 1.0f;
	if (x > a && x < b)
		return (x - a) / (b - a);
	if (x > c && x < d)
		return (d - x) / (d - c);
	return 0.0f;
}

/* ============================================================================
 * Physics Functions
 * =========================================================================== */

static void update_object_physics(AleatoryObject *obj, float dt) {
	int i;

	/* Euler integration */
	for (i = 0; i < 5; i++) {
		obj->velocity[i] += obj->acceleration[i] * dt;
		obj->position[i] += obj->velocity[i] * dt;
	}

	/* Apply damping */
	for (i = 0; i < 5; i++) {
		obj->velocity[i] *= DAMPING_FACTOR;
	}

	/* Update rotation */
	for (i = 0; i < 5; i++) {
		obj->rotation[i] += obj->velocity[i] * dt * 0.5f;
	}

	/* Boundary conditions */
	for (i = 0; i < 3; i++) {
		if (obj->position[i] < -20.0f) {
			obj->position[i] = -20.0f;
			obj->velocity[i] *= -0.5f;
		}
		if (obj->position[i] > 20.0f) {
			obj->position[i] = 20.0f;
			obj->velocity[i] *= -0.5f;
		}
	}
}

/* ============================================================================
 * Object Destruction
 * =========================================================================== */

static void destroy_object(AleatoryWorld *world, int obj_idx) {
	AleatoryObject *obj = &world->objects[obj_idx];
	int i, j;

	if (obj->quantum_brain)
		free(obj->quantum_brain);
	if (obj->aleatory_controller)
		free(obj->aleatory_controller);

	/* Remove from parent's children list */
	if (obj->parent_id >= 0 && obj->parent_id < world->object_count) {
		AleatoryObject *parent = &world->objects[obj->parent_id];
		for (i = 0; i < parent->child_count; i++) {
			if (parent->children[i] == obj->id) {
				for (j = i; j < parent->child_count - 1; j++) {
					parent->children[j] = parent->children[j + 1];
				}
				parent->child_count--;
				break;
			}
		}
	}

	/* Remove from entanglement matrix */
	for (i = 0; i < world->object_count; i++) {
		world->entanglement_matrix[obj_idx][i] = 0.0f;
		world->entanglement_matrix[i][obj_idx] = 0.0f;
	}

	/* Shift remaining objects */
	for (i = obj_idx; i < world->object_count - 1; i++) {
		world->objects[i] = world->objects[i + 1];
		world->objects[i].id = i;
	}

	world->object_count--;
}

/* ============================================================================
 * Aleatory Manifold Generators
 * =========================================================================== */

static int generate_quantum_sphere(AleatoryManifold *m, void *params) {
	int i, j, k, idx;
	float u, v, w;
	float quantum_fluctuation;
	int res = m->resolution;

	(void) params;

	for (i = 0; i < res; i++) {
		for (j = 0; j < res; j++) {
			for (k = 0; k < res; k++) {
				idx = (i * res + j) * res + k;

				u = (float) i / (res - 1) * 2.0f * 3.14159f;
				v = (float) j / (res - 1) * 3.14159f;
				w = (float) k / (res - 1) * 3.14159f;

				/* Add quantum fluctuations */
				quantum_fluctuation = 0.1f * sin(u * 10.0f) * cos(v * 10.0f)
						* sin(w * 10.0f);

				/* Base sphere with quantum uncertainty */
				m->points[idx].position[0] = (float) (sin(v) * cos(u))
						* (1.0f + quantum_fluctuation);
				m->points[idx].position[1] = (float) (sin(v) * sin(u))
						* (1.0f + quantum_fluctuation);
				m->points[idx].position[2] = (float) cos(v)
						* (1.0f + quantum_fluctuation);

				/* Quantum phase and amplitude */
				m->points[idx].position[3] = fmod(u + quantum_fluctuation,
						2.0f * 3.14159f);
				m->points[idx].position[4] = 0.5f
						+ 0.5f * sin(v * 5.0f) * cos(w * 5.0f);

				/* Initialize quantum amplitude */
				quantum_amplitude_init(&m->points[idx].qamp, 0.7f * cos(u),
						0.7f * sin(v));

				m->points[idx].mass = 1.0f / MANIFOLD_POINTS;
				m->points[idx].temperature = 0.5f + 0.3f * sin(w);
				m->points[idx].energy = 1.0f;
				m->points[idx].quantum_potential = 0.1f * quantum_fluctuation;
				m->points[idx].probability_density =
						m->points[idx].qamp.probability;

				/* Initialize chaos at this point */
				m->points[idx].chaos.position[0] = u;
				m->points[idx].chaos.position[1] = v;
				m->points[idx].chaos.position[2] = w;
				m->points[idx].chaos.attractor_type =
						rand() % STRANGE_ATTRACTORS;
			}
		}
	}

	return 1;
}

static int generate_quantum_torus(AleatoryManifold *m, void *params) {
	int i, j, k, idx;
	float u, v, w;
	float R = 2.0f, r = 0.8f;
	float quantum_tunnel;
	int res = m->resolution;

	(void) params;
	(void) w; /* Suppress unused warning */

	for (i = 0; i < res; i++) {
		for (j = 0; j < res; j++) {
			for (k = 0; k < res; k++) {
				idx = (i * res + j) * res + k;

				u = (float) i / (res - 1) * 2.0f * 3.14159f;
				v = (float) j / (res - 1) * 2.0f * 3.14159f;

				/* Quantum tunneling probability */
				quantum_tunnel = 0.2f * (sin(u * 8.0f) * cos(v * 8.0f) + 1.0f)
						* 0.5f;

				/* Torus with quantum tunneling effects */
				m->points[idx].position[0] = (R + r * cos(v)) * cos(u)
						* (1.0f + quantum_tunnel * 0.1f);
				m->points[idx].position[1] = (R + r * cos(v)) * sin(u)
						* (1.0f + quantum_tunnel * 0.1f);
				m->points[idx].position[2] = r * sin(v)
						* (1.0f + quantum_tunnel * 0.1f);

				/* Quantum dimensions */
				m->points[idx].position[3] = fmod(u + v, 2.0f * 3.14159f);
				m->points[idx].position[4] = quantum_tunnel;

				quantum_amplitude_init(&m->points[idx].qamp,
						cos(u) * quantum_tunnel, sin(v) * quantum_tunnel);

				m->points[idx].quantum_potential = -0.5f * quantum_tunnel
						* quantum_tunnel;
				m->points[idx].probability_density =
						m->points[idx].qamp.probability;
			}
		}
	}

	return 1;
}

/* ============================================================================
 * Quantum Neural Network Implementation
 * =========================================================================== */

static void quantum_nn_init(QuantumNeuralNetwork *qnn) {
	int i, j;

	memset(qnn, 0, sizeof(QuantumNeuralNetwork));
	qnn->learning_rate = 0.001f;
	qnn->quantum_temperature = 0.85f;

	/* Initialize quantum weights with complex random values */
	for (i = 0; i < INPUT_NEURONS; i++) {
		for (j = 0; j < HIDDEN_NEURONS; j++) {
			float phase = 2.0f * 3.14159f * ((float) rand() / RAND_MAX);
			float magnitude = ((float) rand() / RAND_MAX) * 0.5f;
			qnn->weights_real[i][j] = magnitude * cos(phase);
			qnn->weights_imag[i][j] = magnitude * sin(phase);
		}
	}

	for (i = 0; i < HIDDEN_NEURONS; i++) {
		qnn->hidden_bias_real[i] = 0.1f * cos((float) i);
		qnn->hidden_bias_imag[i] = 0.1f * sin((float) i);

		for (j = 0; j < OUTPUT_NEURONS; j++) {
			float phase = 2.0f * 3.14159f * ((float) rand() / RAND_MAX);
			float magnitude = ((float) rand() / RAND_MAX) * 0.5f;
			qnn->output_weights_real[i][j] = magnitude * cos(phase);
			qnn->output_weights_imag[i][j] = magnitude * sin(phase);
		}
	}
}

static void quantum_activation(float *amplitude, float *phase, float real,
		float imag) {
	/* Quantum activation function - phase-aware */
	float magnitude = sqrt(real * real + imag * imag);
	*amplitude = tanh(magnitude);
	*phase = atan2(imag, real);
}

static void quantum_nn_forward(QuantumNeuralNetwork *qnn,
		const float *input_real, const float *input_imag) {
	int i, j;
	float sum_real, sum_imag;

	/* Hidden layer quantum computation */
	for (i = 0; i < HIDDEN_NEURONS; i++) {
		sum_real = qnn->hidden_bias_real[i];
		sum_imag = qnn->hidden_bias_imag[i];

		for (j = 0; j < INPUT_NEURONS; j++) {
			/* Complex multiplication: (a+ib)(c+id) = (ac-bd) + i(ad+bc) */
			float a = input_real[j];
			float b = input_imag[j];
			float c = qnn->weights_real[j][i];
			float d = qnn->weights_imag[j][i];

			sum_real += a * c - b * d;
			sum_imag += a * d + b * c;
		}

		quantum_activation(&qnn->hidden_amplitude[i], &qnn->hidden_phase[i],
				sum_real, sum_imag);
	}

	/* Output layer quantum computation */
	for (i = 0; i < OUTPUT_NEURONS; i++) {
		sum_real = qnn->output_bias_real[i];
		sum_imag = qnn->output_bias_imag[i];

		for (j = 0; j < HIDDEN_NEURONS; j++) {
			float a = qnn->hidden_amplitude[j] * cos(qnn->hidden_phase[j]);
			float b = qnn->hidden_amplitude[j] * sin(qnn->hidden_phase[j]);
			float c = qnn->output_weights_real[j][i];
			float d = qnn->output_weights_imag[j][i];

			sum_real += a * c - b * d;
			sum_imag += a * d + b * c;
		}

		quantum_activation(&qnn->output_amplitude[i], &qnn->output_phase[i],
				sum_real, sum_imag);
	}
}

/* ============================================================================
 * Aleatory Fuzzy System Implementation
 * =========================================================================== */

static void aleatory_fuzzy_init(AleatoryFuzzySystem *afs) {
	int i, j, k;
	float step;

	memset(afs, 0, sizeof(AleatoryFuzzySystem));

	for (i = 0; i < FUZZY_INPUTS; i++) {
		afs->inputs[i].min = -1.0f;
		afs->inputs[i].max = 1.0f;
		step = (afs->inputs[i].max - afs->inputs[i].min)
				/ (MEMBERSHIP_SETS - 1);

		for (j = 0; j < MEMBERSHIP_SETS; j++) {
			float center = afs->inputs[i].min + j * step;
			afs->inputs[i].sets[j].a = center - step * 0.8f;
			afs->inputs[i].sets[j].b = center - step * 0.3f;
			afs->inputs[i].sets[j].c = center + step * 0.3f;
			afs->inputs[i].sets[j].d = center + step * 0.8f;

			/* Initialize probability distribution */
			afs->inputs[i].sets[j].dist.mean = center;
			afs->inputs[i].sets[j].dist.variance = step * 0.2f;
			for (k = 0; k < 100; k++) {
				float x = afs->inputs[i].min + k * step * 0.1f;
				afs->inputs[i].sets[j].dist.probability_cloud[k] = exp(
						-(x - center) * (x - center) / (2.0f * step * step));
			}
		}
	}

	/* Initialize rules with quantum probabilities */
	for (i = 0; i < RULE_BASE_SIZE; i++) {
		for (j = 0; j < FUZZY_INPUTS; j++) {
			afs->rules[i].antecedents[j] = rand() % MEMBERSHIP_SETS;
		}
		afs->rules[i].consequent[0] = rand() % MEMBERSHIP_SETS;
		afs->rules[i].weight = 0.5f + 0.5f * quantum_random();
		afs->rules[i].probability = quantum_random();
	}
}

static void aleatory_fuzzy_evaluate(AleatoryFuzzySystem *afs,
		const float *inputs) {
	int i, j;
	float firing;
	float quantum_noise;

	/* Fuzzification with quantum uncertainty */
	for (i = 0; i < FUZZY_INPUTS; i++) {
		afs->inputs[i].crisp = inputs[i];
		for (j = 0; j < MEMBERSHIP_SETS; j++) {
			AleatoryMembership *m = &afs->inputs[i].sets[j];
			float mem = membership_trapezoid(inputs[i], m->a, m->b, m->c, m->d);

			/* Add quantum probability cloud */
			int idx = (int) ((inputs[i] - afs->inputs[i].min) * 50);
			if (idx < 0)
				idx = 0;
			if (idx >= 100)
				idx = 99;
			quantum_noise = m->dist.probability_cloud[idx];

			afs->inputs[i].fuzzy[j] = mem * (0.9f + 0.1f * quantum_noise);
			afs->inputs[i].probability[j] = quantum_noise;
		}
	}

	/* Rule evaluation with quantum interference */
	for (i = 0; i < RULE_BASE_SIZE; i++) {
		firing = 1.0f;

		for (j = 0; j < FUZZY_INPUTS; j++) {
			int ant = afs->rules[i].antecedents[j];
			float mem = afs->inputs[j].fuzzy[ant];
			float prob = afs->inputs[j].probability[ant];

			/* Quantum AND operation */
			firing *= mem * (0.9f + 0.1f * prob);
		}

		afs->rule_activations[i] = firing * afs->rules[i].weight
				* afs->rules[i].probability;
	}
}

/* ============================================================================
 * Aleatory Object Creation
 * =========================================================================== */

static AleatoryObject* create_aleatory_object(AleatoryWorld *world, int type_id,
		vec5 position) {
	AleatoryObject *obj = NULL;
	int i;

	if (world->object_count >= MAX_OBJECTS)
		return NULL;

	obj = &world->objects[world->object_count];
	memset(obj, 0, sizeof(AleatoryObject));

	obj->id = world->object_count;
	obj->type = type_id;
	obj->state = STATE_IDLE;
	obj->age = 0.0f;
	obj->energy = 1.0f;
	obj->health = 1.0f;
	obj->mass = 1.0f;

	vec5_copy(obj->position, position);
	vec5_zero(obj->velocity);
	vec5_zero(obj->acceleration);
	vec5_set(obj->scale, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	vec5_zero(obj->rotation);
	vec5_zero(obj->goal);

	/* Initialize manifold with quantum fluctuations */
	obj->manifold.resolution = MANIFOLD_RESOLUTION;
	obj->manifold.total_points = MANIFOLD_POINTS;

	/* Choose generator based on type */
	switch (type_id % 4) {
	case 0:
		generate_quantum_sphere(&obj->manifold, NULL);
		break;
	case 1:
		generate_quantum_torus(&obj->manifold, NULL);
		break;
	default:
		generate_quantum_sphere(&obj->manifold, NULL);
		break;
	}

	/* Initialize quantum state */
	for (i = 0; i < WAVE_FUNCTION_SIZE; i++) {
		obj->wave_function[i] = quantum_random();
	}

	/* Initialize quantum brain */
	obj->quantum_brain = (QuantumNeuralNetwork*) malloc(
			sizeof(QuantumNeuralNetwork));
	if (obj->quantum_brain) {
		quantum_nn_init(obj->quantum_brain);
	}

	/* Initialize aleatory controller */
	obj->aleatory_controller = (AleatoryFuzzySystem*) malloc(
			sizeof(AleatoryFuzzySystem));
	if (obj->aleatory_controller) {
		aleatory_fuzzy_init(obj->aleatory_controller);
	}

	/* Initialize probability distributions for behavior */
	obj->curiosity.mean = 0.5f;
	obj->curiosity.variance = 0.2f;
	obj->fear.mean = 0.3f;
	obj->fear.variance = 0.3f;
	obj->aggression.mean = 0.2f;
	obj->aggression.variance = 0.4f;
	obj->social_force.mean = 0.4f;
	obj->social_force.variance = 0.2f;

	/* Initialize quantum affinity matrix */
	for (i = 0; i < MAX_OBJECTS; i++) {
		obj->quantum_affinity[i] = quantum_random() * 2.0f - 1.0f;
	}

	obj->parent_id = -1;
	obj->child_count = 0;

	/* Initialize entangled partners to -1 */
	for (i = 0; i < ENTANGLEMENT_PAIRS; i++) {
		obj->entangled_partners[i] = -1;
	}

	/* Entangle with random existing object */
	if (world->object_count > 0) {
		int partner = rand() % world->object_count;
		obj->entangled_partners[0] = partner;
		world->entanglement_matrix[obj->id][partner] = quantum_random();
		world->entanglement_matrix[partner][obj->id] = quantum_random();
	}

	world->object_count++;

	return obj;
}

/* ============================================================================
 * Quantum Evolution and Chaos Dynamics
 * =========================================================================== */

static void evolve_quantum_state(AleatoryObject *obj, float dt) {
	int i;
	float hbar = PLANCK_CONSTANT;

	/* Schrödinger evolution */
	for (i = 0; i < obj->manifold.total_points; i += 10) {
		AleatoryManifoldPoint *p = &obj->manifold.points[i];

		/* Time-dependent Schrödinger equation (simplified) */
		float kinetic = -0.5f * p->quantum_potential;
		float potential = p->energy * p->temperature;
		float hamiltonian = kinetic + potential;

		/* Phase evolution */
		p->position[3] += hamiltonian * dt / hbar;
		p->position[3] = fmod(p->position[3], 2.0f * 3.14159f);

		/* Probability amplitude evolution */
		float real = p->qamp.real * cos(hamiltonian * dt)
				- p->qamp.imag * sin(hamiltonian * dt);
		float imag = p->qamp.real * sin(hamiltonian * dt)
				+ p->qamp.imag * cos(hamiltonian * dt);

		quantum_amplitude_init(&p->qamp, real, imag);
		p->probability_density = p->qamp.probability;
	}
}

static void evolve_chaos_state(AleatoryObject *obj, float dt) {
	int i;

	for (i = 0; i < obj->manifold.total_points; i += 10) {
		AleatoryManifoldPoint *p = &obj->manifold.points[i];
		ChaosState *c = &p->chaos;

		/* Apply appropriate strange attractor */
		switch (c->attractor_type % STRANGE_ATTRACTORS) {
		case 0:
			lorenz_attractor(c->position, dt * 0.1f);
			break;
		case 1:
			roessler_attractor(c->position, dt * 0.1f);
			break;
		default:
			lorenz_attractor(c->position, dt * 0.1f);
			break;
		}

		/* Couple chaos to manifold position */
		obj->position[0] += c->position[0] * dt * 0.01f;
		obj->position[1] += c->position[1] * dt * 0.01f;
		obj->position[2] += c->position[2] * dt * 0.01f;
	}
}

/* ============================================================================
 * Aleatory Physics with Quantum Gravity
 * =========================================================================== */

static void compute_aleatory_forces(AleatoryObject *obj, AleatoryWorld *world) {
	int i;
	float distance;
	vec5 force, dir;
	float quantum_force, chaos_force;

	vec5_zero(force);

	/* Classical gravity */
	force[1] -= obj->mass * GRAVITY_CONSTANT * world->env.gravity[1];

	/* Quantum vacuum fluctuations */
	quantum_force = world->env.vacuum_energy
			* sin(obj->quantum_state.decoherence_time);
	force[0] += quantum_force * 0.01f;
	force[2] += quantum_force * 0.01f;

	/* Chaos coupling */
	chaos_force = world->chaos_coupling * obj->chaos_state.position[3];
	force[0] += chaos_force;
	force[1] += chaos_force * 0.5f;

	/* Quantum entanglement forces */
	for (i = 0; i < ENTANGLEMENT_PAIRS; i++) {
		if (obj->entangled_partners[i] >= 0
				&& obj->entangled_partners[i] < world->object_count) {
			AleatoryObject *partner =
					&world->objects[obj->entangled_partners[i]];

			vec5_sub(dir, partner->position, obj->position);
			distance = vec5_length(dir);

			if (distance > 0.1f) {
				float entangle_force =
						world->entanglement_matrix[obj->id][obj->entangled_partners[i]]
								/ (distance * distance + 0.1f);
				vec5_normalize(dir, dir);
				vec5_mul_scalar(dir, dir, entangle_force);
				vec5_add(force, force, dir);
			}
		}
	}

	/* Update acceleration */
	if (obj->mass > 0) {
		vec5_mul_scalar(obj->acceleration, force, 1.0f / obj->mass);
	}
}

/* ============================================================================
 * Aleatory Decision Making with Quantum Probability
 * =========================================================================== */

static void aleatory_decide(AleatoryObject *obj, AleatoryWorld *world) {
	float inputs[FUZZY_INPUTS];
	float quantum_input_real[INPUT_NEURONS];
	float quantum_input_imag[INPUT_NEURONS];
	int i;

	/* Prepare fuzzy inputs with quantum uncertainty */
	inputs[0] = obj->energy - 0.5f;
	inputs[1] = obj->health - 0.5f;
	inputs[2] = obj->curiosity.mean
			+ obj->curiosity.variance * quantum_random();
	inputs[3] = obj->fear.mean + obj->fear.variance * quantum_random();
	inputs[4] = obj->aggression.mean
			+ obj->aggression.variance * quantum_random();
	inputs[5] = obj->velocity[0] * 0.1f;
	inputs[6] = obj->velocity[1] * 0.1f;
	inputs[7] = obj->velocity[2] * 0.1f;
	inputs[8] = world->env.temperature - 0.5f;
	inputs[9] = world->env.light_intensity - 0.5f;
	inputs[10] = (float) obj->child_count / MAX_OBJECTS;
	inputs[11] = (float) obj->state / STATE_DYING;

	/* Aleatory fuzzy evaluation */
	if (obj->aleatory_controller) {
		aleatory_fuzzy_evaluate(obj->aleatory_controller, inputs);
	}

	/* Quantum neural network decision */
	if (obj->quantum_brain) {
		/* Prepare quantum inputs */
		for (i = 0; i < INPUT_NEURONS; i++) {
			if (i < FUZZY_INPUTS) {
				quantum_input_real[i] = inputs[i];
				quantum_input_imag[i] = 0.1f * quantum_random();
			} else {
				quantum_input_real[i] = quantum_random() * 2.0f - 1.0f;
				quantum_input_imag[i] = quantum_random() * 2.0f - 1.0f;
			}
		}

		quantum_nn_forward(obj->quantum_brain, quantum_input_real,
				quantum_input_imag);

		/* Apply quantum decisions */
		for (i = 0; i < 3; i++) {
			obj->goal[i] += obj->quantum_brain->output_amplitude[i] * 0.1f;
		}
	}

	/* Quantum random walk if no decision */
	if (vec5_length(obj->velocity) < 0.01f) {
		obj->velocity[0] += (quantum_random() - 0.5f) * 0.1f;
		obj->velocity[1] += (quantum_random() - 0.5f) * 0.1f;
		obj->velocity[2] += (quantum_random() - 0.5f) * 0.1f;
	}
}

/* ============================================================================
 * World Update
 * =========================================================================== */

static void update_aleatory_world(AleatoryWorld *world, float dt) {
	int i;

	world->global_time += dt;

	/* Update quantum foam */
	world->env.quantum_foam_density = 0.3f
			+ 0.2f * sin(world->global_time * 0.5f);
	world->env.vacuum_energy = 0.1f + 0.05f * cos(world->global_time * 0.3f);
	world->env.higgs_field = 0.5f + 0.1f * sin(world->global_time * 0.2f);

	/* Update all objects */
	for (i = 0; i < world->object_count; i++) {
		AleatoryObject *obj = &world->objects[i];

		/* Quantum evolution */
		evolve_quantum_state(obj, dt);
		evolve_chaos_state(obj, dt);

		/* Physics */
		compute_aleatory_forces(obj, world);
		update_object_physics(obj, dt);

		/* Decision making */
		aleatory_decide(obj, world);

		/* Update quantum glow */
		obj->quantum_glow = 0.5f
				+ 0.5f * sin(obj->quantum_state.decoherence_time * 10.0f);
		obj->quantum_state.decoherence_time += dt * DECOHERENCE_RATE;

		/* Quantum tunneling reproduction */
		if (obj->energy > 0.8f && obj->child_count < 3
				&& quantum_random() < 0.01f) { /* 1% chance */
			vec5 child_pos;
			vec5_copy(child_pos, obj->position);
			child_pos[0] += 3.0f * (quantum_random() - 0.5f);
			child_pos[1] += 3.0f * (quantum_random() - 0.5f);

			AleatoryObject *child = create_aleatory_object(world,
					(obj->type + 1) % 4, child_pos);
			if (child) {
				child->parent_id = obj->id;
				obj->children[obj->child_count++] = child->id;
				obj->energy *= 0.6f;

				/* Quantum entanglement between parent and child */
				child->entangled_partners[0] = obj->id;
				world->entanglement_matrix[child->id][obj->id] =
						quantum_random();
			}
		}
	}

	/* Remove decohered objects */
	for (i = world->object_count - 1; i >= 0; i--) {
		if (world->objects[i].quantum_state.decoherence_time > 1.0f) {
			destroy_object(world, i);
		}
	}
}

/* ============================================================================
 * Rendering Functions
 * =========================================================================== */

static void render_aleatory_object(SDL_Renderer *renderer, AleatoryObject *obj,
		int view_x, int view_y, float scale) {
	int i, j, x, y;
	float proj_x, proj_y;
	float quantum_glow = obj->quantum_glow;

	/* Calculate projection */
	proj_x = view_x + obj->position[0] * scale;
	proj_y = view_y + obj->position[1] * scale;

	/* Quantum glow effect - probability cloud */
	SDL_SetRenderDrawColor(renderer, (Uint8) (100 * quantum_glow),
			(Uint8) (50 * quantum_glow), (Uint8) (200 * quantum_glow),
			(Uint8) (128 * quantum_glow));

	for (i = -10; i <= 10; i++) {
		for (j = -10; j <= 10; j++) {
			float dist = sqrt((float) (i * i + j * j)) / 10.0f;
			float prob =
					exp(
							-dist * dist
									/ (2.0f
											* obj->quantum_state.decoherence_time
											+ 0.1f));
			if (quantum_random() < prob) {
				x = (int) proj_x + i * 2;
				y = (int) proj_y + j * 2;
				if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT) {
					SDL_RenderDrawPoint(renderer, x, y);
				}
			}
		}
	}

	/* Draw main object points with quantum phase colors */
	for (i = 0; i < obj->manifold.total_points; i += 20) {
		AleatoryManifoldPoint *p = &obj->manifold.points[i];
		float phase = p->position[3];
		float prob = p->probability_density;

		x = (int) (proj_x + p->position[0] * obj->scale[0] * 15.0f);
		y = (int) (proj_y + p->position[1] * obj->scale[1] * 15.0f);

		if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT) {
			/* Color based on quantum phase */
			Uint8 r = (Uint8) (128 + 127 * sin(phase));
			Uint8 g = (Uint8) (128 + 127 * sin(phase + 2.09f));
			Uint8 b = (Uint8) (128 + 127 * sin(phase + 4.18f));

			SDL_SetRenderDrawColor(renderer, r, g, b, (Uint8) (255 * prob));
			SDL_RenderDrawPoint(renderer, x, y);
		}
	}

	/* Draw energy/quantum bar */
	int bar_width = 40;
	int bar_height = 6;
	int bar_x = (int) proj_x - bar_width / 2;
	int bar_y = (int) proj_y - 30;

	/* Energy bar (classical) */
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_Rect bg_rect;
	bg_rect.x = bar_x;
	bg_rect.y = bar_y;
	bg_rect.w = bar_width;
	bg_rect.h = bar_height;
	SDL_RenderDrawRect(renderer, &bg_rect);

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	int fill_width = (int) (obj->energy * bar_width);
	for (i = 0; i < fill_width; i++) {
		for (j = 0; j < bar_height; j++) {
			SDL_RenderDrawPoint(renderer, bar_x + i, bar_y + j);
		}
	}

	/* Quantum coherence bar */
	bar_y -= 8;
	bg_rect.y = bar_y;
	SDL_SetRenderDrawColor(renderer, 128, 0, 255, 255);
	SDL_RenderDrawRect(renderer, &bg_rect);

	fill_width =
			(int) ((1.0f - obj->quantum_state.decoherence_time) * bar_width);
	SDL_SetRenderDrawColor(renderer, 200, 100, 255, 255);
	for (i = 0; i < fill_width; i++) {
		for (j = 0; j < bar_height; j++) {
			SDL_RenderDrawPoint(renderer, bar_x + i, bar_y + j);
		}
	}

	/* Draw quantum type indicator */
	char label[64];
	sprintf(label, "Q%d", obj->type);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	for (i = 0; i < (int) strlen(label); i++) {
		SDL_RenderDrawPoint(renderer, bar_x + i * 8, bar_y - 10);
	}
}

static void render_aleatory_world(AleatoryWorld *world, SDL_Renderer *renderer) {
	int i;
	int center_x = WINDOW_WIDTH / 2;
	int center_y = WINDOW_HEIGHT / 2;
	float scale = 8.0f;

	/* Clear with quantum foam background */
	SDL_SetRenderDrawColor(renderer, 5, 5, 10, 255);
	SDL_RenderClear(renderer);

	/* Draw quantum foam */
	SDL_SetRenderDrawColor(renderer, 20, 0, 40, 64);
	for (i = 0; i < 500; i++) {
		int x = rand() % WINDOW_WIDTH;
		int y = rand() % WINDOW_HEIGHT;
		if (quantum_random() < world->env.quantum_foam_density) {
			SDL_RenderDrawPoint(renderer, x, y);
		}
	}

	/* Draw grid */
	SDL_SetRenderDrawColor(renderer, 40, 20, 60, 128);
	for (i = -20; i <= 20; i++) {
		int x = center_x + i * (int) scale;
		if (x >= 0 && x < WINDOW_WIDTH) {
			SDL_RenderDrawLine(renderer, x, 0, x, WINDOW_HEIGHT);
		}
	}
	for (i = -15; i <= 15; i++) {
		int y = center_y + i * (int) scale;
		if (y >= 0 && y < WINDOW_HEIGHT) {
			SDL_RenderDrawLine(renderer, 0, y, WINDOW_WIDTH, y);
		}
	}

	/* Draw all objects */
	for (i = 0; i < world->object_count; i++) {
		render_aleatory_object(renderer, &world->objects[i], center_x, center_y,
				scale);
	}

	/* Draw quantum HUD */
	char buffer[256];
	sprintf(buffer, "Objects: %d | Gen: %d | Quantum Foam: %.3f",
			world->object_count, world->generation,
			world->env.quantum_foam_density);

	SDL_SetRenderDrawColor(renderer, 180, 100, 255, 255);
	for (i = 0; i < (int) strlen(buffer); i++) {
		SDL_RenderDrawPoint(renderer, 20 + i * 8, 20);
	}

	SDL_RenderPresent(renderer);
}

/* ============================================================================
 * Main Application
 * =========================================================================== */

int main(int argc, char *argv[]) {
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Event event;
	AleatoryWorld world;
	double last_time, current_time;
	float dt;
	int running = 1;
	int i;

	(void) argc;
	(void) argv;

	/* Initialize random seed */
	srand((unsigned int) time(NULL));

	log_message("EVOX Aleatory 5D v%s starting...", PROGRAM_VERSION);
	log_message("Quantum foam density: %.3f", 0.3f);
	log_message("Vacuum energy: %.3f", 0.1f);

	/* Initialize SDL */
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		log_message("SDL init failed: %s", SDL_GetError());
		return EXIT_FAILURE;
	}

	window = SDL_CreateWindow(PROGRAM_NAME,
	SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED,
	WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

	if (!window) {
		log_message("Window creation failed: %s", SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}

	renderer = SDL_CreateRenderer(window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!renderer) {
		log_message("Renderer creation failed: %s", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return EXIT_FAILURE;
	}

	/* Initialize aleatory world */
	memset(&world, 0, sizeof(AleatoryWorld));

	/* Initialize environment */
	vec3_set(world.env.gravity, 0.0f, -1.0f, 0.0f); /* Normalized gravity */
	world.env.temperature = 0.5f;
	world.env.light_intensity = 1.0f;
	world.env.quantum_foam_density = 0.3f;
	world.env.vacuum_energy = 0.1f;
	world.env.higgs_field = 0.5f;
	vec3_set(world.env.light_direction, 1.0f, -1.0f, 1.0f);

	world.quantum_decoherence_rate = DECOHERENCE_RATE;
	world.chaos_coupling = CHAOS_COUPLING;

	/* Create initial quantum objects */
	for (i = 0; i < 4; i++) {
		vec5 pos;
		vec5_set(pos, (float) (rand() % 20 - 10), (float) (rand() % 20 - 10),
				(float) (rand() % 20 - 10), quantum_random() * 2.0f * 3.14159f,
				quantum_random());
		create_aleatory_object(&world, i % 4, pos);
	}

	log_message("Aleatory world initialized with %d quantum objects",
			world.object_count);
	log_message("Quantum entanglement active");

	last_time = get_time();

	/* Main quantum loop */
	while (running) {
		/* Process events */
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = 0;
			} else if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					running = 0;
				} else if (event.key.keysym.sym == SDLK_c) {
					/* Create new quantum object */
					vec5 pos;
					vec5_set(pos, (float) (rand() % 20 - 10),
							(float) (rand() % 20 - 10),
							(float) (rand() % 20 - 10),
							quantum_random() * 2.0f * 3.14159f,
							quantum_random());
					create_aleatory_object(&world, rand() % 4, pos);
					log_message("Quantum object created, total: %d",
							world.object_count);
				} else if (event.key.keysym.sym == SDLK_r) {
					/* Reset quantum world */
					for (i = 0; i < world.object_count; i++) {
						if (world.objects[i].quantum_brain)
							free(world.objects[i].quantum_brain);
						if (world.objects[i].aleatory_controller)
							free(world.objects[i].aleatory_controller);
					}
					memset(&world, 0, sizeof(AleatoryWorld));

					/* Reinitialize */
					vec3_set(world.env.gravity, 0.0f, -1.0f, 0.0f);
					world.env.quantum_foam_density = 0.3f;
					world.env.vacuum_energy = 0.1f;
					world.quantum_decoherence_rate = DECOHERENCE_RATE;
					world.chaos_coupling = CHAOS_COUPLING;

					for (i = 0; i < 4; i++) {
						vec5 pos;
						vec5_set(pos, (float) (rand() % 20 - 10),
								(float) (rand() % 20 - 10),
								(float) (rand() % 20 - 10),
								quantum_random() * 2.0f * 3.14159f,
								quantum_random());
						create_aleatory_object(&world, i % 4, pos);
					}
					log_message("Quantum world reset");
				}
			}
		}

		/* Calculate delta time */
		current_time = get_time();
		dt = (float) (current_time - last_time);
		if (dt > 0.1f)
			dt = 0.1f;
		last_time = current_time;

		/* Update aleatory world */
		update_aleatory_world(&world, dt);

		/* Render quantum visualization */
		render_aleatory_world(&world, renderer);

		/* Quantum delay */
		SDL_Delay(16);
	}

	/* Cleanup */
	for (i = 0; i < world.object_count; i++) {
		if (world.objects[i].quantum_brain)
			free(world.objects[i].quantum_brain);
		if (world.objects[i].aleatory_controller)
			free(world.objects[i].aleatory_controller);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	log_message("EVOX Aleatory 5D shutdown complete.");
	log_message("Quantum foam collapsed.");
	return EXIT_SUCCESS;
}
