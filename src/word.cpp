#include "word.h"

CWord :: CWord(const QDomElement& src)
{
    id = src.attribute(XML_ID);
    QDomNodeList content = src.childNodes();
    for (int i = 0; i < content.length(); i++) {
        QDomNode itemNode = content.item(i);
        if (!itemNode.isElement())
            continue;
        QDomElement item = itemNode.toElement();
        QString tag_name = item.tagName();
        // Разобрать структуру блока слова
        if (tag_name == XML_FORM1) {  // get form1
            form1 = item.attribute(XML_ID);
            form1_sound = item.attribute(XML_SOUND);
            form1_transcr = item.text();
        }
        else if (tag_name == XML_FORM2) { // get form2
            form2 = item.attribute(XML_ID);
            form2_sound = item.attribute(XML_SOUND);
            form2_transcr = item.text();
        }
        else if (tag_name == XML_FORM3) { // get form3
            form3 = item.attribute(XML_ID);
            form3_sound = item.attribute(XML_SOUND);
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
        else continue;  // skip over an unexpected tag
    }
}

CWord :: ~CWord() {}

/* Проверить слово */
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
    result.state = flag;
    return result;
}

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

/* Read a formatted text form dictionary */
QString CWord :: getFormattedText(const QDomElement &element)
{
    QString res("");
    QDomNodeList content = element.childNodes();
    for (int i = 0; i < content.size(); i++) {
        QDomNode item = content.item(i);
        if (item.isElement()) {
            QDomElement subelem = item.toElement();
            QString tag = subelem.tagName();
            if (tag == "g")
                res += QString("<font color=\"%1\">%2</font>").arg("#00DD00", getFormattedText(subelem));   // ALARM! Recursion!
            else if (tag == "gi")
                res += QString("<i><font color=\"%1\">%2</font><i/>").arg("#00DD00", getFormattedText(subelem));    // ALARM! Recursion!
            else
                res += QString("<%1>%2</%1>").arg(tag, getFormattedText(subelem));
        }
        else if (item.isComment()) {
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
