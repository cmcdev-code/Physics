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
	#define get_i_position get_x_position
 
	T get_y_position() const {
		return position.y;
	}
	#define get_j_position get_y_position

	T get_z_position() const {
		return position.z;
	}
	#define get_k_position get_z_position

	T get_x_velocity() const {
		return velocity.x;
	}
	#define get_j_velocity get_x_velocity

	T get_y_velocity() const {
		return velocity.y;
	}
	#define get_j_velocity get_y_velocity

	T get_z_velocity() const {
		return velocity.z;
	}
	#define get_k_velocity get_z_velocity

	T get_x_accleration() const {
		return accleration.x;
	}
	#define get_i_accleration get_x_accleration

	T get_y_accleration() const {
		return accleration.y;
	}
	#define get_j_accleration get_y_accleration

	T get_z_accleration() const {
		return accleration.z;
	}
	#define get_k_accleration get_z_accleration
	
	void set_x_position(T xP) {
		position.x = xP;
	}
	#define set_i_position set_x_position

	void set_y_position(T yP) {
		position.y = yP;
	}
	#define set_j_position set_y_postion

	void set_z_position(T zP) {
		position.z = zP;
	}
	#define set_k_position set_z_position

	void set_x_velocity(T xV) {
		velocity.x = xV;
	}
	#define set_i_velocity set_x_velocity

	void set_y_velocity(T yV) {
		velocity.y = yV;
	}
	#define set_j_velocity set_y_velocity

	void set_z_velocity(T zV) {
		velocity.z = zV;
	}
	#define set_k_velocity set_z_velocity

	void set_x_accleration(T xA) {
		accleration.x = xA;
	}
	#define set_i_accleration set_x_accleration

	void set_y_accleration(T yA) {
		accleration.y = yA;
	}
	#define set_j_accleration set_y_accleration 

	void set_z_accleration(T zA) {
		accleration.z = zA;
	}
	#define set_k_accleration set_z_accleration

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
	
	bool operator==(const particle& particle_2) const {
		return (temp == particle_2.get_temp() &&
			mass == particle_2.get_mass() &&
			radius == particle_2.get_radius() &&
			position.x == particle_2.get_x_position() &&
			position.y == particle_2.get_y_position() &&
			position.z == particle_2.get_z_position() &&
			velocity.x == particle_2.get_x_velocity() &&
			velocity.y == particle_2.get_y_velocity() &&
			velocity.z == particle_2.get_z_velocity() &&
			accleration.x == particle_2.get_x_accleration() &&
			accleration.y == particle_2.get_y_accleration() &&
			accleration.z == particle_2.get_z_accleration());
	}
	bool operator!=(const particle& particle_2) const {
		return !(*this == particle_2);
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