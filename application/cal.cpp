#ifndef __JWD_AND_HELPER_20051005
#define __JWD_AND_HELPER_20051005

#include <math.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

#ifndef PI
#define PI 3.14159265
#endif

static double Rc = 6378137;  // 赤道半径

static double Rj = 6356725;  // 极半径


static double MY_FLT_MIN = 1.175494351e-5F;     //最小的浮点数据
static double EE = 0.0066943799;                //偏心率

struct CDpPosition
{
    double  m_fLongitude;       //经度  度
    double  m_fLatitude;        //纬度  度
    float   m_fHeight;          //高度  米
    float   m_fPlatSpeed;       //地速  4   米/秒
    float   m_fPlatPitch;       //俯仰  4   度
    float   m_fPlatRoll;        //横滚  4   度
    float   m_fTrueHead;        //航向  4   度
    float   m_fDeclineAngle;    //偏流角    4   度
    float   m_fTrackAngle;      //航迹角    4   度
    CDpPosition()
    {
        memset(this, 0, sizeof(*this));
    }
};

typedef CDpPosition* PDpPosition;


class JWD
{
    public:
        double m_LoDeg, m_LoMin, m_LoSec;  // longtitude 经度
        double m_LaDeg, m_LaMin, m_LaSec;
        double m_Longitude, m_Latitude;
        double m_RadLo, m_RadLa;
        double Ec;
        double Ed;
    public:
        // 构造函数, 经度: loDeg 度, loMin 分, loSec 秒;  纬度: laDeg 度, laMin 分, laSec秒
        JWD(double loDeg, double loMin, double loSec, double laDeg, double laMin, double laSec)
        {
            m_LoDeg=loDeg;
            m_LoMin=loMin;
            m_LoSec=loSec;
            m_LaDeg=laDeg;
            m_LaMin=laMin;
            m_LaSec=laSec;
            m_Longitude = m_LoDeg + m_LoMin / 60 + m_LoSec / 3600;
            m_Latitude = m_LaDeg + m_LaMin / 60 + m_LaSec / 3600;
            m_RadLo  = (m_Longitude * PI)/180.0;
            m_RadLa  = (m_Latitude * PI)/180.0;
            Ec = Rj + (Rc - Rj) * (90.0- m_Latitude) / 90.0;
            Ed = Ec * cos(m_RadLa);
        }
        // 构造函数, 经度: loDeg 度, loMin 分, loSec 秒;  纬度: laDeg 度, laMin 分, laSec秒
        JWD(bool isE,double loDeg, double loMin, double loSec, bool isS,double laDeg, double laMin, double laSec)
        {
            m_LoDeg=loDeg;
            m_LoMin=loMin;
            m_LoSec=loSec;
            m_LaDeg=laDeg;
            m_LaMin=laMin;
            m_LaSec=laSec;
            m_Longitude = m_LoDeg + m_LoMin / 60 + m_LoSec / 3600;
            if(!isE)
                m_Longitude = 0 - m_Longitude;
            m_Latitude = m_LaDeg + m_LaMin / 60 + m_LaSec / 3600;
            if(!isS)
                m_Latitude = 0 - m_Latitude;
            m_RadLo  = (m_Longitude * PI)/180.0;
            m_RadLa  = (m_Latitude * PI)/180.0;
            Ec = Rj + (Rc - Rj) * (90.0- m_Latitude) / 90.0;
            Ed = Ec * cos(m_RadLa);
        }

        //！
        JWD(double longitude, double latitude)
        {
            m_LoDeg = int(longitude);
            m_LoMin = int((longitude - m_LoDeg)*60);
            m_LoSec = (longitude - m_LoDeg - m_LoMin/60.)*3600;

            m_LaDeg = int(latitude);
            m_LaMin = int((latitude - m_LaDeg)*60);
            m_LaSec = (latitude - m_LaDeg - m_LaMin/60.)*3600;

            m_Longitude = longitude;
            m_Latitude = latitude;
            m_RadLo = longitude * PI/180.0;
            m_RadLa = latitude * PI/180.0;
            Ec = Rj + (Rc - Rj) * (90.-m_Latitude) / 90.0;
            Ed = Ec * cos(m_RadLa);
        }
};

class CJWDHelper
{
    public:
        CJWDHelper() {};
        ~CJWDHelper() {};

        //! 计算点A 和 点B的经纬度，求他们的距离和点B相对于点A的方位
        /*!
         * \param A A点经纬度
         * \param B B点经纬度
         * \param angle B相对于A的方位, 不需要返回该值，则将其设为空
         * \return A点B点的距离
         */
        static double distance(JWD A, JWD B, double *angle)
        {
            double dx = (B.m_RadLo - A.m_RadLo) * A.Ed;
            double dy = (B.m_RadLa - A.m_RadLa) * A.Ec;
            double out = sqrt(dx * dx + dy * dy);

            if( angle != NULL)
            {
                *angle = atan(fabs(dx/dy))*180./PI;
                // 判断象限
                double dLo = B.m_Longitude - A.m_Longitude;
                double dLa = B.m_Latitude - A.m_Latitude;

                if(dLo > 0 && dLa <= 0)
                {
                    *angle = (90. - *angle) + 90.0;
                }
                else if(dLo <= 0 && dLa < 0)
                {
                    *angle = *angle + 180.;
                }
                else if(dLo < 0 && dLa >= 0)
                {
                    *angle = (90. - *angle) + 270;
                }
            }
            return out/1000;
        }

        //! 计算点A 和 点B的经纬度，求他们的距离和点B相对于点A的方位
        /*!
         * \param longitude1 A点经度
         * \param latitude1 A点纬度
         * \param longitude2 B点经度
         * \param latitude2 B点纬度
         * \param angle B相对于A的方位, 不需要返回该值，则将其设为空
         * \return A点B点的距离
         */
        static double distance(
                double longitude1, double latitude1,
                double longitude2, double latitude2,
                double *angle)
        {
            JWD A(longitude1,latitude1);
            JWD B(longitude2,latitude2);

            return distance(A, B, angle);
        }

        //! 已知点A经纬度，根据B点据A点的距离，和方位，求B点的经纬度
        /*!
         * \param A 已知点A
         * \param distance B点到A点的距离
         * \param angle B点相对于A点的方位
         * \return B点的经纬度坐标
         */
        static JWD GetJWDB(JWD A, double distance, double angle)
        {
            double dx = distance*1000 * sin(angle * PI /180.0);
            double dy = distance*1000 * cos(angle * PI /180.0);

            //double dx = (B.m_RadLo - A.m_RadLo) * A.Ed;
            //double dy = (B.m_RadLa - A.m_RadLa) * A.Ec;

            double BJD = (dx/A.Ed + A.m_RadLo) * 180.0/PI;
            double BWD = (dy/A.Ec + A.m_RadLa) * 180.0/PI;
            JWD B(BJD, BWD);
            return B;
        }

        //! 已知点A经纬度，根据B点据A点的距离，和方位，求B点的经纬度
        /*!
         * \param longitude 已知点A经度
         * \param latitude 已知点A纬度
         * \param distance B点到A点的距离
         * \param angle B点相对于A点的方位
         * \return B点的经纬度坐标
         */

        static JWD GetJWDB(double longitude, double latitude, double distance, double angle)
        {
            JWD ret(0., 0.);
            return ret;

            /**
              JWD A(longitude,latitude);
              return GetJWDB(A, distance, angle);
             **/
        }

        static JWD GetJWDB_GE(double longitude, double latitude, double distance, double angle)
        {
            JWD A(longitude,latitude);
            return GetJWDB(A, distance, angle);
        }



        static double EstimateDoa(PDpPosition pPosOri, PDpPosition pPosNew)
        {
            PDpPosition pPosRef = pPosOri ;
            PDpPosition pPosObj = pPosNew ;
            double    fStationLon;        //侦察站经度
            double    fStationLat;        //侦察站纬度
            double    fObjLong;           //目标经度
            double    fObjLat;            //目标纬度
            double    fEstDoa;            //到达方位角估计值
            fStationLon   = pPosRef->m_fLongitude*PI/180;
            fStationLat   = pPosRef->m_fLatitude*PI/180;
            fObjLong  = pPosObj->m_fLongitude*PI/180;
            fObjLat       = pPosObj->m_fLatitude*PI/180;

            if ((fStationLat <= fObjLat+MY_FLT_MIN)&&(fStationLat >= fObjLat-MY_FLT_MIN))//相同维度
            {
                if (fStationLon < fObjLong)//基站在左边
                {
                    return 90.0f;
                }
                else//右边
                {
                    return 270.0f;
                }
            }
            if ((fStationLon <= fObjLong+MY_FLT_MIN)&&(fStationLon >= fObjLong-MY_FLT_MIN))//相同经度
            {
                if (fStationLat > fObjLat)//基站在上
                {
                    return 180.0f;
                }
                else
                {
                    return 0.0f;
                }
            }
            //根据侦察站的位置和目标位置计算到达方位角
            fEstDoa=PI/2 - atan(
                    cos(fStationLat)/sin(fObjLong - fStationLon)*
                    (tan(fObjLat)-tan(fStationLat)*cos(fObjLong - fStationLon)-EE*
                     (tan(fObjLat)-sin(fStationLat)/cos(fObjLat)*sqrt((1-EE*sin(fObjLat)*sin(fObjLat))/
                                                                      (1-EE*sin(fStationLat)*sin(fStationLat)))
                     )
                    )
                    );

            fEstDoa *= (180/PI);

            if (fObjLong < fStationLon)
            {
                fEstDoa += 180;
            }

            if ( fEstDoa > 360.0f )
            {
                fEstDoa -= 360.0f;
            }

            return fEstDoa;
        }

};

int main(int argc, char **argv)
{
    if (argc < 5)
    {
        printf("0\n0\n");
        return -1;
    }
    double a_lon, a_lat, b_lon, b_lat;
    sscanf(argv[1], "%lf", &a_lat);
    sscanf(argv[2], "%lf", &a_lon);
    sscanf(argv[3], "%lf", &b_lat);
    sscanf(argv[4], "%lf", &b_lon);
    JWD ap(a_lat, a_lon);
    JWD bp(b_lat, b_lon);
    double angle;
    double dis = CJWDHelper::distance(ap, bp, &angle);
    printf("%f\n%f\n", dis, angle);
    return 0;
}

#endif

