/*
***Copyleft (C) 2020 Softwater, Inc
***Contact: bogdyname@gmail.com
*/

#include "Data/cryptography.h"

Cryptography::Cryptography():
    m_key(0), m_compressionMode(Cryptography::CompressionAuto),
    m_protectionMode(Cryptography::ProtectionChecksum),
    m_lastError(Cryptography::ErrorNoError)
{
    qsrand(uint(QDateTime::currentMSecsSinceEpoch() & 0xFFFF));

    return;
}

Cryptography::Cryptography(quint64 key):
    m_key(key), m_compressionMode(Cryptography::CompressionAuto),
    m_protectionMode(Cryptography::ProtectionChecksum),
    m_lastError(Cryptography::ErrorNoError)
{
    qsrand(uint(QDateTime::currentMSecsSinceEpoch() & 0xFFFF));
    Cryptography::splitKey();

    return;
}

Cryptography::~Cryptography()
{

    return;
}

void Cryptography::setKey(quint64 key)
{
    Cryptography::m_key = key;
    Cryptography::splitKey();

    return;
}

void Cryptography::splitKey()
{
    Cryptography::m_keyParts.QVector::clear();
    Cryptography::m_keyParts.QVector::resize(8);

    for (int i = 0; i < 8; i++)
    {
        quint64 part = Cryptography::m_key;

        for (int j = i; j > 0; j--)
            part = part >> 8;

        part = part & 0xff;
        Cryptography::m_keyParts[i] = static_cast<char>(part);
    }

    return;
}

QByteArray Cryptography::encryptToByteArray(const QString& plaintext)
{
    QByteArray plaintextArray = plaintext.QString::toUtf8();

    return Cryptography::encryptToByteArray(plaintextArray);
}

QByteArray Cryptography::encryptToByteArray(QByteArray plaintext)
{
    if (Cryptography::m_keyParts.QVector::isEmpty())
    {
        qWarning() << "No key set.";
        Cryptography::m_lastError = Cryptography::ErrorNoKeySet;

        return QByteArray();
    }

    QByteArray ba = plaintext;

    CryptoFlags flags = Cryptography::CryptoFlagNone;
    if (Cryptography::m_compressionMode == Cryptography::CompressionAlways)
    {
        ba = qCompress(ba, 9); //maximum compression
        flags |= Cryptography::CryptoFlagCompression;
    }
    else if (Cryptography::m_compressionMode == Cryptography::CompressionAuto)
    {
        QByteArray compressed = qCompress(ba, 9);
        if (compressed.QByteArray::count() < ba.QByteArray::count())
        {
            ba = compressed;
            flags |= Cryptography::CryptoFlagCompression;
        }
    }

    QByteArray integrityProtection;

    if (Cryptography::m_protectionMode == Cryptography::ProtectionChecksum)
    {
        flags |= Cryptography::CryptoFlagChecksum;
        QDataStream stream(&integrityProtection, QIODevice::WriteOnly);
        stream << qChecksum(ba.QByteArray::constData(), ba.QByteArray::length());
    }
    else if (Cryptography::m_protectionMode == ProtectionHash)
    {
        flags |= Cryptography::CryptoFlagHash;
        QCryptographicHash hash(QCryptographicHash::Sha1);
        hash.QCryptographicHash::addData(ba);

        integrityProtection += hash.QCryptographicHash::result();
    }

    //prepend a random char to the string
    char randomChar = char(qrand() & 0xFF);
    ba = randomChar + integrityProtection + ba;

    int pos(0);
    char lastChar(0);

    int cnt = ba.QByteArray::count();

    while (pos < cnt)
    {
        ba[pos] = ba.QByteArray::at(pos) ^ m_keyParts.QVector::at(pos % 8) ^ lastChar;
        lastChar = ba.QByteArray::at(pos);
        ++pos;
    }

    QByteArray resultArray;
    resultArray.QByteArray::append(char(0x03));
    resultArray.QByteArray::append(char(flags)); //encryption flags
    resultArray.QByteArray::append(ba);

    m_lastError = Cryptography::ErrorNoError;

    return resultArray;
}

QString Cryptography::encryptToString(const QString& plaintext)
{
    QByteArray plaintextArray = plaintext.QString::toUtf8();
    QByteArray cypher = Cryptography::encryptToByteArray(plaintextArray);
    QString cypherString = QString::fromLatin1(cypher.QByteArray::toBase64());

    return cypherString;
}

QString Cryptography::encryptToString(QByteArray plaintext)
{
    QByteArray cypher = Cryptography::encryptToByteArray(plaintext);
    QString cypherString = QString::fromLatin1(cypher.QByteArray::toBase64());

    return cypherString;
}

QString Cryptography::decryptToString(const QString &cyphertext)
{
    QByteArray cyphertextArray = QByteArray::fromBase64(cyphertext.QString::toLatin1());
    QByteArray plaintextArray = Cryptography::decryptToByteArray(cyphertextArray);
    QString plaintext = QString::fromUtf8(plaintextArray, plaintextArray.QByteArray::size());

    return plaintext;
}

QString Cryptography::decryptToString(QByteArray cypher)
{
    QByteArray ba = Cryptography::decryptToByteArray(cypher);
    QString plaintext = QString::fromUtf8(ba, ba.QByteArray::size());

    return plaintext;
}

QByteArray Cryptography::decryptToByteArray(const QString& cyphertext)
{
    QByteArray cyphertextArray = QByteArray::fromBase64(cyphertext.QString::toLatin1());
    QByteArray ba = Cryptography::decryptToByteArray(cyphertextArray);

    return ba;
}

QByteArray Cryptography::decryptToByteArray(QByteArray cypher)
{
    if (Cryptography::m_keyParts.QVector::isEmpty())
    {
        qWarning() << "No key set.";
        Cryptography::m_lastError = Cryptography::ErrorNoKeySet;

        return QByteArray();
    }

    QByteArray ba = cypher;

    if(cypher.QByteArray::count() < 3)
        return QByteArray();

    char version = ba.QByteArray::at(0);

    if (version != 3)
    {
        Cryptography::m_lastError = Cryptography::ErrorUnknownVersion;
        qWarning() << "Invalid version or not a cyphertext.";

        return QByteArray();
    }

    CryptoFlags flags = CryptoFlags(ba.QByteArray::at(1));

    ba = ba.QByteArray::mid(2);
    int pos(0);
    int cnt(ba.QByteArray::count());
    char lastChar = 0;

    while (pos < cnt)
    {
        char currentChar = ba[pos];
        ba[pos] = ba.QByteArray::at(pos) ^ lastChar ^ Cryptography::m_keyParts.QVector::at(pos % 8);
        lastChar = currentChar;
        ++pos;
    }

    ba = ba.QByteArray::mid(1); //chop off the random number at the start

    bool integrityOk(true);
    if (flags.QFlags::testFlag(Cryptography::CryptoFlagChecksum))
    {
        if (ba.QByteArray::length() < 2)
        {
            Cryptography::m_lastError = Cryptography::ErrorIntegrityFailed;

            return QByteArray();
        }

        quint16 storedChecksum;
        {
            QDataStream stream(&ba, QIODevice::ReadOnly);
            stream >> storedChecksum;
        }

        ba = ba.QByteArray::mid(2);
        quint16 checksum = qChecksum(ba.QByteArray::constData(), ba.QByteArray::length());
        integrityOk = (checksum == storedChecksum);
    }
    else if (flags.QFlags::testFlag(Cryptography::CryptoFlagHash))
    {
        if (ba.QByteArray::length() < 20)
        {
            Cryptography::m_lastError = Cryptography::ErrorIntegrityFailed;

            return QByteArray();
        }

        QByteArray storedHash = ba.QByteArray::left(20);
        ba = ba.QByteArray::mid(20);
        QCryptographicHash hash(QCryptographicHash::Sha1);
        hash.QCryptographicHash::addData(ba);
        integrityOk = (hash.QCryptographicHash::result() == storedHash);
    }

    if (!integrityOk)
    {
        Cryptography::m_lastError = Cryptography::ErrorIntegrityFailed;

        return QByteArray();
    }

    if (flags.QFlags::testFlag(Cryptography::CryptoFlagCompression))
        ba = qUncompress(ba);

    Cryptography::m_lastError = Cryptography::ErrorNoError;

    return ba;
}
