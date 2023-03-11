#ifndef PARTICLE_HPP
#define PARTICLE_HPP

template<typename T>
struct vec3 {
	vec3() {
		x = 0;
		y = 0;
		z = 0;
	}
	vec3(T x1, T y1, T z1) {
		x = x1;
		y = y1;
		z = z1;
	}
	union {
		T x;
		T i;
	};
	union
	{
		T y;
		T j;
	};
	union {
		T z;
		T k;
	};
};

template <typename T>
class particle {
	
public:

	//Constructors
	particle() {
		position.x = 0.0f;
		position.y = 0.0f;
		position.z = 0.0f;

		velocity.x = 0.0f;
		velocity.y = 0.0f;
		velocity.z = 0.0f;

		accleration.x = 0.0f;
		accleration.y = 0.0f;
		accleration.z = 0.0f;
		mass = 0.0f;
		temp = 0.0f;
		radius = 0.0f;
	}
	particle(vec3<T> position_, vec3<T> velocity_, vec3<T> accleration_, T mass_, T temp_, T radius_) :
		position{ position_ },velocity{velocity_},accleration{accleration_}
	{
		mass = mass_;
		temp = temp_;
		radius = radius_;
	}

	T get_x_position() const {
		return position.x;
	}
	T get_i_position() const {
		return position.i;
	}
	T get_y_position() const {
		return position.y;
	}
	T get_j_position() const {
		return position.j;
	}
	T get_z_position() const {
		return position.z;
	}
	T get_k_position() const {
		return position.k;
	}

	T get_x_velocity() const {
		return velocity.x;
	}
	T get_i_velocity() const {
		return velocity.i;
	}
	T get_y_velocity() const {
		return velocity.y;
	}
	T get_j_velocity() const {
		return velocity.j;
	}
	T get_z_velocity() const {
		return velocity.z;
	}
	T get_k_velocity() const {
		return velocity.k;
	}


	T get_x_accleration() const {
		return accleration.x;
	}
	T get_i_accleration() const {
		return accleration.i;
	}
	T get_y_accleration() const {
		return accleration.y;
	}
	T get_j_accleration() const {
		return accleration.j;
	}
	T get_z_accleration() const {
		return accleration.z;
	}
	T get_k_accleration() const {
		return accleration.k;
	}
	
	void set_x_position(T xP) {
		position.x = xP;
	}
	void set_i_position(T iP) {
		position.i = iP;
	}
	void set_y_position(T yP) {
		position.y = yP;
	}
	void set_j_position(T jP) {
		position.j = jP;
	}
	void set_z_position(T zP) {
		position.z = zP;
	}
	void set_k_position(T kP) {
		position.k = kP;
	}

	void set_x_velocity(T xV) {
		velocity.x = xV;
	}
	void set_i_velocity(T iV) {
		velocity.i = iV;
	}
	void set_y_velocity(T yV) {
		velocity.y = yV;
	}
	void set_j_velocity(T jV) {
		velocity.j = jV;
	}
	void set_z_velocity(T zV) {
		velocity.z = zV;
	}
	void set_k_velocity(T kV) {
		velocity.k = kV;
	}

	void set_x_accleration(T xA) {
		accleration.x = xA;
	}
	void set_i_accleration(T iA) {
		accleration.i = iA;
	}
	void set_y_accleration(T yA) {
		accleration.y = yA;
	}
	void set_j_accleration(T jA) {
		accleration.j = jA;
	}
	void set_z_accleration(T zA) {
		accleration.z = zA;
	}
	void set_k_accleration(T kA) {
		accleration.k = kA;
	}
	T get_temp() const {
		return temp;
	}
	T get_mass() const {
		return mass;
	}
	T get_radius() const {
		return radius;
	}
	void set_temp(T t) {
		temp = t;
	}
	void set_mass(T m) {
		mass = m;
	}
	void set_radius(T r) {
		radius = r;
	}

private:
	vec3<T> position;
	vec3<T> velocity;
	vec3<T> accleration;

	T temp;
	T mass;
	T radius;
};
#endif