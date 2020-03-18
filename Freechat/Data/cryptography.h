/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#ifndef CRYPTOGRAPHY_H
#define CRYPTOGRAPHY_H

#include <QFile>
#include <QVector>
#include <QtDebug>
#include <QtGlobal>
#include <QDateTime>
#include <QByteArray>
#include <QCryptographicHash>
#include <QDataStream>
#include <math.h>
#include <iostream>

class Cryptography : public QFile
{
    Q_OBJECT
    Q_CLASSINFO("Version", "1.0")

public:
    Cryptography();
    explicit Cryptography(quint64 m_key);
    ~Cryptography();

    enum CompressionMode
    {
         CompressionAuto,
         CompressionAlways,
         CompressionNever
    };

    enum IntegrityProtectionMode
    {
         ProtectionNone,
         ProtectionChecksum,
         ProtectionHash
    };

    enum Error
    {
         ErrorNoError,
         ErrorNoKeySet,
         ErrorUnknownVersion,
         ErrorIntegrityFailed
    };

    void setKey(quint64 m_key);

    bool hasKey() const {return !m_keyParts.isEmpty();}
    void setCompressionMode(CompressionMode mode) {m_compressionMode = mode;}
    CompressionMode compressionMode() const {return m_compressionMode;}
    void setIntegrityProtectionMode(IntegrityProtectionMode mode) {m_protectionMode = mode;}
    IntegrityProtectionMode integrityProtectionMode() const {return m_protectionMode;}
    Error lastError() const {return m_lastError;}

    QString encryptToString(const QString& plaintext);
    QString encryptToString(QByteArray plaintext);
    QByteArray encryptToByteArray(const QString& plaintext);
    QByteArray encryptToByteArray(QByteArray plaintext);
    QString decryptToString(const QString& cyphertext);
    QByteArray decryptToByteArray(const QString& cyphertext);
    QString decryptToString(QByteArray cypher);
    QByteArray decryptToByteArray(QByteArray cypher);

    enum CryptoFlag
    {
        CryptoFlagNone = 0,
        CryptoFlagCompression = 0x01,
        CryptoFlagChecksum = 0x02,
        CryptoFlagHash = 0x04
    };

    Q_DECLARE_FLAGS(CryptoFlags, CryptoFlag);

private:
        void splitKey();

        quint64 m_key;
        QVector<char> m_keyParts;
        CompressionMode m_compressionMode;
        IntegrityProtectionMode m_protectionMode;
        Error m_lastError;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(Cryptography::CryptoFlags)

#endif
