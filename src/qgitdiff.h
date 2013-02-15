#ifndef QGITDIFF_H
#define QGITDIFF_H

#include <QStringList>
#include <QMultiMap>
#include <git2/diff.h>

#include "qgitobject.h"
#include "qgittree.h"
#include "qgitrepository.h"
#include "qgittree.h"

namespace LibQGit2
{
    class QGitRepository;
    class QGitCommit;

    class LIBQGIT2_EXPORT QGitDiff : public QGitObject
    {
    public:
         QGitDiff(QGitRepository repo, QGitCommit commitFrom, QGitCommit commitTo);

         virtual ~QGitDiff();

         QStringList getFileChangedList();

         QString getDeltasForFile(const QString &file);

         // public so they can be called from the c callback code
         void addFileDiff(const char *delta);
         void addFileChanged(const git_diff_delta *delta);
         void addPatchHunks(const git_diff_delta *delta, const char *header, int headerLen);
         void addPatchLines(const git_diff_delta *delta, const char *line, char usage, int lineLen);
    private:
         QStringList fileList;
         // Maps filename to patch hunk
         QMap<QString, QString> deltas;
         git_diff_list *diff;

    };
}
#endif // QGITDIFF_H