#pragma once
#include "hitable.h"

class Sphere : public Hittable
{
public:
	Sphere() {}
	Sphere(vec3 _center, float _radius) : center(_center), radius(_radius);
	virtual bool Hit(const Ray& ray, float t_min, float t_max, HitResult& result) const;

	vec3 center;
	float radius;
};

bool Sphere::Hit(const Ray& r, float t_min, float t_max, HitResult& rec) const
{
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = dot(oc, r.direction());
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - a * c;
	if (discriminant > 0) {
		float temp = (-b - sqrt(discriminant)) / a;
		if (temp < t_max && temp > t_min) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			return true;
		}
		temp = (-b + sqrt(discriminant)) / a;
		if (temp < t_max && temp > t_min) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			return true;
		}
	}
	return false;
}