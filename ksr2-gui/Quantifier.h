#ifndef QUANTIFIER_H
#define QUANTIFIER_H

#include "Common.h"

#include <QObject>
#include <QTextStream>
#include <QMetaType>

class Quantifier : public QObject
{
    Q_OBJECT
public:
    explicit Quantifier(QObject *parent = 0);
    explicit Quantifier(const QString &name, const QList<double> &values,
                        const Range &range, const QString &type, QObject *parent = 0);
    Quantifier(const Quantifier &q);
    QString quantName() const;
    void setQuantName(const QString &name);
    QList<double> values() const;
    void setValues(const QList<double> &val);
    Range range() const;
    void setRange(const Range &range);
    QString typeName() const;
    void setTypeName(const QString &name);

    friend QTextStream& operator<<(QTextStream &qs, const Quantifier& obj);

signals:

public slots:

private:
    QString mName;
    QList<double> mValues;
    Range mRange;
    QString mTypeName;
};

Q_DECLARE_METATYPE(Quantifier)

#endif // QUANTIFIER_H
