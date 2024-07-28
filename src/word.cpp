/* ****************************************************************************
 * File:    word.cpp
 * Author:  Chumakov Anton I.
 * Date:    June 15, 2024
 * ****************************************************************************/

#include "word.h"
#include "settings_key.h"

extern QSettings* appSettings;

CWord :: CWord(const QDomElement& element)
    : source(element)
{
    id = source.attribute(XML_ID);
    QDir snd_path(appSettings->value(ini_system::sound_path).toString());
    QDomNodeList content = source.childNodes();
    for (int i = 0; i < content.length(); i++) {
        QDomNode itemNode = content.item(i);
        if (!itemNode.isElement())
            continue;
        QDomElement item = itemNode.toElement();
        QString tag_name = item.tagName();
        // analyse the structure of 'word'
        if (tag_name == XML_FORM1) {  // get form1
            form1 = item.attribute(XML_ID);
            form1_sound = snd_path.absoluteFilePath(item.attribute(XML_SOUND));
            form1_transcr = item.text();
        }
        else if (tag_name == XML_FORM2) { // get form2  // TODO: form2 might be an array
            form2 = item.attribute(XML_ID);
            form2_sound = snd_path.absoluteFilePath(item.attribute(XML_SOUND));
            form2_transcr = item.text();
        }
        else if (tag_name == XML_FORM3) { // get form3  // TODO: form3 might be an array
            form3 = item.attribute(XML_ID);
            form3_sound = snd_path.absoluteFilePath(item.attribute(XML_SOUND));
            form3_transcr = item.text();
        }
        else if (tag_name == XML_TRANSLATION)   // get translation
            translation.push_back(getFormattedText(item));
        else if (tag_name == XML_EXAMPLE) {     // get example
            QDomNodeList lst = item.elementsByTagName(XML_TEXT);
            QDomNode lstNode = lst.item(0);
            QDomElement lstEl = lstNode.toElement();
            QString etext = lstEl.text();
            example.push_back(etext);

            lst = item.elementsByTagName(XML_TRANSLATION);
            lstNode = lst.item(0);
            lstEl = lstNode.toElement();
            example_transl.push_back(etext + " --> " + lstEl.text());
        }
        else if (tag_name == "statistics") {
            qDebug() << "[CWord: read statistics] <-- TODO!";
        }
        else continue;  // skip over an unexpected tag
    }
}

/** @Check the word */
Result CWord :: check(const QString inp2, const QString inp3, const QString inpTrns)
{
    Result result;
    bool flag = true;
    if (!inp2.isEmpty() && inp2.toLower() == form2) // check 2nd form
        result.form2 = format(form2, colorGreen, true) + QString(" [%1]").arg(form2_transcr);
    else {
        QString s = inp2;
        if (!inp2.isEmpty())
            s = QString("<s>%1</s><br>").arg(inp2);
        result.form2 = s + QString("<b>%1</b> [%2]").arg(form2, form2_transcr);
        flag &= false;
    }
    if (!inp3.isEmpty() && inp3.toLower() == form3) // check 3rd form
        result.form3 = format(form3, colorGreen, true) + QString(" [%1]").arg(form3_transcr);
    else {
        QString s = inp3;
        if (!inp3.isEmpty())
            s = QString("<s>%1</s><br>").arg(inp3);
        result.form3 = s + QString("<b>%1</b> [%2]").arg(form3, form3_transcr);
        flag &= false;
    }
    bool flagT = false;
    foreach (auto item, translation) {  // check translation
        if (!inpTrns.isEmpty() && item.startsWith(inpTrns, Qt::CaseInsensitive)) {
            flagT = true;   // One match is enought
            break;
        }
        else continue;
    }
    if (flagT)
        result.translation = translation.join("; ");    //format(translation.join("; "), colorGreen);
    else {
        QString s = inpTrns;
        if (!inpTrns.isEmpty())
            s = QString("<s>%1</s><br>").arg(inpTrns);
        result.translation = s + translation.join("; ");
        flag &= false;
    }
    //updateStatistics(flag);
    result.state = flag;
    return result;
}

// TODO: likely it's an useless function. Give formating to the style of GUI
/** @Applies an HTML-fotmat to string */
QString CWord :: format(QString s, QString color, bool bold, bool italic)
{
    if (!s.isEmpty()) {
        if (!color.isEmpty())
            s = QString("<font color=\"%1\">%2</font>").arg(color, s);
        if (bold)
            s = QString("<b>%1</b>").arg(s);
        if (italic)
            s = QString("<i>%1</i>").arg(s);
    }
    return s;
}

/** @Read a formatted text form element (recursive algorithm) */
QString CWord :: getFormattedText(const QDomElement &element)
{
    QString res("");
    QDomNodeList content = element.childNodes();
    for (int i = 0; i < content.size(); i++) {
        QDomNode item = content.item(i);
        if (item.isElement()) {
            QDomElement subelem = item.toElement();
            QString tag = subelem.tagName();
            if (tag == "g") // TODO: remove magic constants
                res += QString("<font color=\"%1\">%2</font>").arg(colorGreen, getFormattedText(subelem));
            else if (tag == "gi")
                res += QString("<i><font color=\"%1\">%2</font><i/>").arg(colorGreen, getFormattedText(subelem));
            else
                res += QString("<%1>%2</%1>").arg(tag, getFormattedText(subelem));
        }
        else if (item.isComment()) {    // Why?
            QDomComment comm = item.toComment();
            res += QString("<!--%1-->").arg(comm.data());
        }
        else {
            QDomText txt = item.toText();
            res += txt.nodeValue();
        }
    }
    return res; //element.text();
}
