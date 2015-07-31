/**************************************************************************
 * Copyright (c) 2015 Raffaele Pertile <raffarti@zoho.com>
 * This file is part of touchegg-gce.
 *
 * touchegg-gce is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * touchegg-gce is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with touchegg-gce.  If not, see <http://www.gnu.org/licenses/>.
**************************************************************************/

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

#define var_names(str1,str2) str_ ## str1 ## _ ## str2
#define fun_names(str1,str2) str1 ## _ ## str2
#define set_names(str1,str2) set_ ## str1 ## _ ## str2
#define str_names(str1,str2) #str1 "/" #str2

#define generate_gs(str1, str2,t,f)\
    public:\
    static constexpr const char * var_names(str1,str2) = str_names(str1,str2);\
    t fun_names(str1,str2) (){ \
        return value(str_names(str1,str2)). f ();\
    }\
    public slots:\
    void set_names(str1,str2)(const t &val){\
        setValue(str_names(str1,str2),val);\
    }

#define generate_gs_1(str,t,f)\
    public:\
    static constexpr const char * str_ ## str = #str;\
    t str (){ \
        return value(#str). f ();\
    }\
    public slots:\
    void set_ ## str (const t &val){\
        setValue(#str,val);\
    }

class Settings : public QSettings
{
    Q_OBJECT

    generate_gs(Locale,language,QString,toString)
    generate_gs(Locale,dictsPath,QString,toString)
    generate_gs_1(filePath,QString,toString)
    generate_gs_1(resourcesPath,QString,toString)

public:
    static Settings *instance();

private:
    explicit Settings();
    static Settings *m_instance;

signals:

};

#endif // SETTINGS_H
