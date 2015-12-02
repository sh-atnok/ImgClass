#include <algorithm>
#include <cassert>
#include <cmath>
#include <list>

#include <cstdio>
#include <fstream>
#include <string>
#include <iostream>




// ----- Constructor -----
template <class T>
Segmentation<T>::Segmentation(void)
{
	_width = 0;
	_height = 0;
	_kernel_spatial = 10.0;
	_kernel_intensity = 0.1;
}

template <class T>
Segmentation<T>::Segmentation(const Segmentation<T>& segments) // Copy constructor
{
	_width = segments._width;
	_height = segments._height;
	_kernel_spatial = segments._kernel_spatial;
	_kernel_intensity = segments._kernel_intensity;

	_image.copy(segments._image);
	_shift_vector.copy(segments._shift_vector);
	_segments.copy(segments._segments);
}

template <class T>
Segmentation<T>::Segmentation(const ImgVector<T>* image, const double kernel_spatial_radius, const double kernel_intensity_radius)
{
	_image.copy(image);
	if (_image.max() > 1.0) {
		// Normalize
		_image.contrast_stretching(0.0, 1.0);
	}
	_width = _image.width();
	_height = _image.height();
	_kernel_spatial = kernel_spatial_radius;
	_kernel_intensity = kernel_intensity_radius;

	_shift_vector.reset(_width, _height);
	_segments.reset(_width, _height);

	// Initial Segmentation
	Segmentation_MeanShift();
}


template <class T>
Segmentation<T> &
Segmentation<T>::reset(const ImgVector<T>* image, const double kernel_spatial_radius, const double kernel_intensity_radius)
{
	_image.copy(image);
	if (_image.max() > 1.0) {
		// Normalize
		_image.contrast_stretching(0.0, 1.0);
	}
	_width = _image.width();
	_height = _image.height();
	_kernel_spatial = kernel_spatial_radius;
	_kernel_intensity = kernel_intensity_radius;

	_segments.reset(_width, _height);
	_shift_vector.reset(_width, _height);

	// Initial Segmentation
	Segmentation_MeanShift();
	return *this;
}

template <class T>
Segmentation<T> &
Segmentation<T>::copy(const Segmentation<T>* segments)
{
	_width = segments->_width;
	_height = segments->_height;
	_kernel_spatial = segments->_kernel_spatial;
	_kernel_intensity = segments->_kernel_intensity;

	_image.copy(segments->_image);
	_shift_vector.copy(segments->_shift_vector);
	_segments.copy(segments->_segments);
	return *this;
}

template <class T>
Segmentation<T> &
Segmentation<T>::copy(const Segmentation<T>& segments)
{
	_width = segments._width;
	_height = segments._height;
	_kernel_spatial = segments._kernel_spatial;
	_kernel_intensity = segments._kernel_intensity;

	_image.copy(segments._image);
	_shift_vector.copy(segments._shift_vector);
	_segments.copy(segments._segments);
	return *this;
}


// ----- Destructor -----
template <class T>
Segmentation<T>::~Segmentation(void)
{
}




// ----- Data -----
template <class T>
const ImgVector<int> &
Segmentation<T>::ref_segments(void) const
{
	return _segments;
}

// ----- Accessor -----
template <class T>
int
Segmentation<T>::width(void) const
{
	return _width;
}

template <class T>
int
Segmentation<T>::height(void) const
{
	return _height;
}


template <class T>
int & 
Segmentation<T>::operator[](int n)
{
	return _segments[n];
}

template <class T>
int & 
Segmentation<T>::at(int n)
{
	assert(0 <= n && n < _width * _height);
	return _segments[n];
}

template <class T>
int & 
Segmentation<T>::at(int x, int y)
{
	return _segments.at(x, y);
}

template <class T>
int & 
Segmentation<T>::at_repeat(int x, int y)
{
	return _segments.at_repeat(x, y);
}

template <class T>
int & 
Segmentation<T>::at_mirror(int x, int y)
{
	return _segments.at_mirror(x, y);
}


template <class T>
int
Segmentation<T>::get(int n) const
{
	return _segments.get(n);
}

template <class T>
int
Segmentation<T>::get(int x, int y) const
{
	return _segments.get(x, y);
}

template <class T>
int
Segmentation<T>::get_zeropad(int x, int y) const
{
	return _segments.get_zeropad(x, y);
}

template <class T>
int
Segmentation<T>::get_repeat(int x, int y) const
{
	return _segments.get_repeat(x, y);
}

template <class T>
int
Segmentation<T>::get_mirror(int x, int y) const
{
	return _segments.get_mirror(x, y);
}




// ----- Mean Shift -----

template <class T>
void
Segmentation<T>::Segmentation_MeanShift(int Iter_Max)
{
	if (_width <= 0 || _height <= 0) {
		return;
	}
#pragma omp parallel for schedule(dynamic)
	for (int y = 0; y < _height; y++) {
		for (int x = 0; x < _width; x++) {
			_shift_vector.at(x, y) = MeanShift_Grayscale(x, y, Iter_Max);
			_segments.at(x, y) = 255 * _image.get_zeropad((int)round(_shift_vector.get(x, y).x), (int)round(_shift_vector.get(x, y).y));
		}
	}
	// Output vectors
	FILE *fp;
	fp = fopen("segment_vector.dat", "w");
	fprintf(fp, "%d %d\n", _width, _height);
	for (int y = 0; y < _height; y++)
		for (int x = 0; x < _width; x++)
			_segments.at(x, y) = 0;
	for (int y = 0; y < _height; y++) {
		for (int x = 0; x < _width; x++) {
			_shift_vector.at(x, y).x -= x;
			_shift_vector.at(x, y).y -= y;
			fwrite(&(_shift_vector.get(x, y).x), sizeof(double), 1, fp);
			fwrite(&(_shift_vector.get(x, y).y), sizeof(double), 1, fp);
			if (0 <= (int)round(_shift_vector.get(x, y).x) && (int)round(_shift_vector.get(x, y).x) < _width
			    && 0 <= (int)round(_shift_vector.get(x, y).y) && (int)round(_shift_vector.get(x, y).y) < _height)
				_segments.at(x + (int)round(_shift_vector.get(x, y).x), y + (int)round(_shift_vector.get(x, y).y)) = 255 * _image.get_zeropad(x, y);
		}
	}
	fclose(fp);
}

/*
 * std::vector<double> kernel has kernel radius for each dimensions.
 * The values it needs are below:
 *	kernel_spatial : the spatial radius of mean shift kernel
 *	kernel_intensity : the intensity threshold of mean shift kernel
 */
template <class T>
const VECTOR_2D<double>
Segmentation<T>::MeanShift_Grayscale(const int x, const int y, int Iter_Max)
{
	VECTOR_2D<double> u;
	T intensity;
	std::list<VECTOR_2D<int> > pel_list;

	// Make pixel list
	for (int m = -_kernel_spatial; m <= _kernel_spatial; m++) {
		for (int n = -_kernel_spatial; n <= _kernel_spatial; n++) {
			if (sqrt(n * n + m * m) < _kernel_spatial) {
				VECTOR_2D<int> r(n, m);
				pel_list.push_back(r);
			}
		}
	}
	// Initialize
	u.x = x;
	u.y = y;
	intensity = _image.get(x, y);
	// Iterate until it converge
	for (int i = 0; i < Iter_Max; i++) {
		double N = 0.0;
		T sum_intensity_diff = 0.0;
		VECTOR_2D<double> sum_d(0.0, 0.0);
		VECTOR_2D<double> d_tmp;

		for (std::list<VECTOR_2D<int> >::iterator ite = pel_list.begin(); ite != pel_list.end(); ++ite) {
			VECTOR_2D<double> r(u.x + ite->x, u.y + ite->y);

			if (0 <= r.x && r.x < _width && 0 <= r.y && r.y < _height) {
				double intensity_diff = _image.get(r.x, r.y) - intensity;

				if (fabs(intensity_diff) <= _kernel_intensity) {
					double coeff = (fabs(intensity_diff / _kernel_intensity) - 1.0) * (fabs(intensity_diff / _kernel_intensity) - 1.0);
					N += coeff;
					sum_intensity_diff += intensity_diff * coeff;
					sum_d.x += ite->x * coeff;
					sum_d.y += ite->y * coeff;
				}
			}
		}
		intensity += sum_intensity_diff / N;
		d_tmp.x = std::min(sum_d.x / N, 1.0);
		d_tmp.y = std::min(sum_d.y / N, 1.0);
		if (fabs(_image.get(u.x + d_tmp.x, u.y + d_tmp.y) - intensity) > _kernel_intensity / 2) {
			break;
		} else if (Vector_2D::norm(d_tmp) < 0.1) {
			u += d_tmp;
			break;
		}
		u += d_tmp;
	}
	return u;
}
