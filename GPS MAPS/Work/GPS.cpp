#include "GPS.h"
#include <cmath>
#include <iostream>
namespace GPS

{
    double degreeToRadian(const double& aDegree)
    {
        return aDegree * consts::DegreeToRadianCoof;
    }
    double toRadian(const Latitude& aLat)
    {

        return aLat.point().degree * consts::DegreeToRadianCoof;
    }

    double toRadian(const Longitude& aLong)
    {

        return aLong.point().degree * consts::DegreeToRadianCoof;
    }
    double radianToDegree(const double& aRadian)
    {
        return aRadian * consts::RadianToDegreeCoof;
    }
    bool latitudeIsCorrect(double aDegree)
    {
        return    (aDegree >= consts::LatitudeLeftRange) && (aDegree <= consts::LatitudeRightRange);
    }
    bool longitudeIsCorrect(double aDegree)
    {
        return    (aDegree >= consts::LongitudeLeftRange) && (aDegree <= consts::LongitudeRightRange);
    }
    double minutes(const double& aDegree)
    {
        return 60. * (aDegree - (int)aDegree);
    }

    double minutes(const Latitude& aLat)
    {
        return 60. * (aLat.point().degree - (int)(aLat.point().degree));
    }

    double minutes(const Longitude& aLon)
    {
        return 60. * (aLon.point().degree - (int)(aLon.point().degree));
    }

    double seconds(const double& aDegree)
    {
        double minutes = 60. * (aDegree - (int)aDegree);
        return 60. * (minutes - (int)minutes);
    }
    double seconds(const Latitude& aLat)
    {
        double minutes = 60. * (aLat.point().degree - (int)aLat.point().degree);
        return 60. * (minutes - (int)minutes);
    }
    double seconds(const Longitude& aLon)
    {
        double minutes = 60. * (aLon.point().degree - (int)aLon.point().degree);
        return 60. * (minutes - (int)minutes);
    }

    const degreeDM& toDM(const Latitude& aLat)
    {
        static degreeDM res{ 0.0, 0.0, 'N' };
        res.degree = std::fabs((int)aLat.point().degree);
        res.minutes = std::fabs(minutes(aLat.point().degree));
        res.ch = aLat.point().ch;
        return res;
    }
    const degreeDM& toDM(const Longitude& aLong)
    {
        static degreeDM res{ 0.0, 0.0, 'E' };
        res.degree = std::fabs((int)aLong.point().degree);
        res.minutes = std::fabs(minutes(aLong.point().degree));
        res.ch = aLong.point().ch;
        return res;
    }

    const degreeDMS& toDMS(const Latitude& aLat)
    {
        static degreeDMS res{ 0.0, 0.0, 0.0, 'N' };
        res.degree = std::fabs((int)aLat.point().degree);
        res.minutes = std::fabs((int)minutes(aLat.point().degree));
        res.seconds = std::fabs(seconds(aLat.point().degree));
        res.ch = aLat.point().ch;
        return res;

    }
    const degreeDMS& toDMS(const Longitude& aLong)
    {
        static degreeDMS res{ 0.0, 0.0, 0.0, 'E' };
        res.degree = std::fabs((int)aLong.point().degree);
        res.minutes = std::fabs((int)minutes(aLong.point().degree));
        res.seconds = std::fabs(seconds(aLong.point().degree));
        res.ch = aLong.point().ch;

        return res;
    }

    double courseAzimuth(const Point2D& aP1, const Point2D& aP2, const Point2D& aP3)
    {
        double az1 = aP1.azimuthTo(aP2);
        double az2 = aP2.azimuthTo(aP3);
        double res = 0.;

        if (az1 >= 0.0 && az1 < 90.0)

            res = (az2 - 90.0) + (90.0 - az1);


        if (az1 >= 90.0 && az1 < 180.0)

            res = (az2 - 180.0) + (180.0 - az1);


        if (az1 >= 180.0 && az1 < 270.0)

            res = (az2 - 270.0) + (270.0 - az1);


        if (az1 >= 270.0 && az1 <= 360.0)

            res = (az2 - 360.0) + (360.0 - az1);


        if (res < 0.0)

            res = 360.0 + res;



        return res;

    }

    Latitude::Latitude(double aDegree) :Point{ aDegree, 'N' }
    {

        Correct();
    }
    Latitude::Latitude(const Latitude& other) : Point{ other.Point.degree, other.Point.ch }
    {

    }
    Latitude& Latitude::operator=(const Latitude& aObj)
    {

        if (this == &aObj)

            return *this;

        Point.degree = aObj.Point.degree;

        Point.ch = aObj.Point.ch;

        return *this;

    }

    Latitude::~Latitude()
    {

    }
    bool Latitude::operator==(const Latitude& aRhs) const
    {

        return Point.degree == aRhs.Point.degree;
    }
    bool Latitude::operator!=(const Latitude& aRhs) const
    {
        return !(*this == aRhs);

    }
    void Latitude::Correct()
    {
        if (!latitudeIsCorrect(Point.degree))
        {

            if (Point.degree >= 0.0)
                Point.degree = consts::LatitudeRightRange;
            else
                Point.degree = consts::LatitudeLeftRange;

        }

        Point.ch = (Point.degree >= 0.0) ? 'N' : 'S';

    }
    const degreeD& Latitude::point()const

    {

        return Point;

    }

    Longitude::Longitude(double aDegree) :Point{ aDegree, 'E' }
    {

        Correct();

    }

    Longitude::Longitude(const Longitude& other) :Point{ other.Point.degree, other.Point.ch }
    {

    }

    Longitude& Longitude::operator=(const Longitude& aObj)
    {
        if (this == &aObj)

            return *this;

        Point.degree = aObj.Point.degree;

        Point.ch = aObj.Point.ch;

        return *this;
    }

    Longitude::~Longitude()
    {

    }
    bool Longitude::operator==(const Longitude& aRhs) const
    {

        return Point.degree == aRhs.Point.degree;

    }

    bool Longitude::operator!=(const Longitude& aRhs) const
    {

        return !(*this == aRhs);
    }
    void Longitude::Correct()
    {

        if (!longitudeIsCorrect(Point.degree))
        {
            if (Point.degree >= 0.0)
                Point.degree = consts::LongitudeRightRange;

            else
                Point.degree = consts::LongitudeLeftRange;

        }

        Point.ch = (Point.degree >= 0.0) ? 'E' : 'W';

    }
    const degreeD& Longitude::point()const
    {
        return Point;
    }

    Point2D::Point2D(double aLatitude, double aLongitude, std::string aDescription) :mLatitude(aLatitude), mLongitude(aLongitude), mDescription(aDescription)
    {

    }
    Point2D::Point2D(const Latitude& aLat, const Longitude& aLong, std::string aDescription) : mLatitude(aLat), mLongitude(aLong), mDescription(aDescription)
    {

    }
    Point2D::Point2D(const Point2D& aObj) : mLatitude(aObj.mLatitude), mLongitude(aObj.mLongitude), mDescription(aObj.mDescription)
    {

    }
    Point2D& Point2D::operator=(const Point2D& aObj)
    {

        if (this == &aObj)

            return *this;

        mLatitude = aObj.mLatitude;

        mLongitude = aObj.mLongitude;

        mDescription = aObj.mDescription;

        return *this;
    }
    const Latitude& Point2D::latitude()const
    {
        return mLatitude;
    }

    const Longitude& Point2D::longitude()const
    {
        return mLongitude;
    }
    const std::string& Point2D::description()const
    {
        return mDescription;
    }

    bool Point2D::operator==(const Point2D& aRhs) const
    {
        return (mLatitude == aRhs.mLatitude) && (mLongitude == aRhs.mLongitude);
    }

    bool Point2D::operator!=(const Point2D& aRhs) const
    {
        return !(operator ==(aRhs));
    }
    double Point2D::distanceTo(const Point2D& aTarget) const
    {

        double a1 = toRadian(mLatitude);
        double a2 = toRadian(mLongitude);
        double b1 = toRadian(aTarget.mLatitude);
        double b2 = toRadian(aTarget.mLongitude);

        double t1 = std::cos(a1) * std::cos(a2) * std::cos(b1) * std::cos(b2);
        double t2 = std::cos(a1) * std::sin(a2) * std::cos(b1) * std::sin(b2);
        double t3 = std::sin(a1) * std::sin(b1);
        double tt = std::acos(t1 + t2 + t3);

        return consts::EarthRadiusM * tt;

    }

    double Point2D::azimuthTo(const Point2D& aTarget) const
    {

        double lat1 = toRadian(mLatitude);
        double lat2 = toRadian(aTarget.mLatitude);
        double long1 = toRadian(mLongitude);
        double long2 = toRadian(aTarget.mLongitude);



        double cl1 = std::cos(lat1);
        double cl2 = std::cos(lat2);
        double sl1 = std::sin(lat1);
        double sl2 = std::sin(lat2);

        double delta = long2 - long1;
        double cdelta = std::cos(delta);
        double sdelta = std::sin(delta);

        double y = std::sqrt(std::pow(cl2 * sdelta, 2) + std::pow(cl1 * sl2 - sl1 * cl2 * cdelta, 2));

        double x = sl1 * sl2 + cl1 * cl2 * cdelta;
        x = (cl1 * sl2) - (sl1 * cl2 * cdelta);
        y = sdelta * cl2;
        double z = ((std::atan(-y / x)) * 180.0) / consts::PI;

        if (x < 0)
            z = z + 180.0;


        double z2 = std::fmod((z + 180.0), 360.0) - 180.0;

        z2 = -1.0 * ((consts::PI * z2) / 180.0);

        double anglerad2 = z2 - ((2 * consts::PI) * std::floor((z2 / (2 * consts::PI))));

        return (anglerad2 * 180.0) / consts::PI;
    }
}


