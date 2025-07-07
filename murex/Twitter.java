import java.util.*;

public class Twitter {
    private int time = 0;
    private Map<Integer, Set<Integer>> followees = new HashMap<>();
    private Map<Integer, List<Tweet>> tweets = new HashMap<>();

    private class Tweet {
        int time;
        int tweetId;
        Tweet(int time, int tweetId) {
            this.time = time;
            this.tweetId = tweetId;
        }
    }

    public void postTweet(int userId, int tweetId) {
        tweets.putIfAbsent(userId, new ArrayList<>());
        tweets.get(userId).add(0, new Tweet(time++, tweetId));
    }

    public List<Integer> getNewsFeed(int userId) {
        PriorityQueue<Tweet> pq = new PriorityQueue<>((a, b) -> b.time - a.time);
        Set<Integer> users = new HashSet<>(followees.getOrDefault(userId, new HashSet<>()));
        users.add(userId);

        for (int uid : users) {
            List<Tweet> userTweets = tweets.getOrDefault(uid, new ArrayList<>());
            for (int i = 0; i < Math.min(10, userTweets.size()); i++) {
                pq.offer(userTweets.get(i));
            }
        }

        List<Integer> result = new ArrayList<>();
        while (!pq.isEmpty() && result.size() < 10) {
            result.add(pq.poll().tweetId);
        }
        return result;
    }

    public void follow(int followerId, int followeeId) {
        followees.putIfAbsent(followerId, new HashSet<>());
        followees.get(followerId).add(followeeId);
    }

    public void unfollow(int followerId, int followeeId) {
        followees.getOrDefault(followerId, new HashSet<>()).remove(followeeId);
    }
}
